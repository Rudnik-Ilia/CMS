from flask import Flask, request, jsonify, make_response, abort, Response
import pika
from pika import exceptions
from threading import Thread
from sender_telegram import send_to_telegram
from retry import retry
from prometheus_client import Gauge, generate_latest

app = Flask(__name__)
service_metric = Gauge('service_metric', 'Description of service_metric')
HOST = "rabbitmq"
PORT = 5672


@retry(pika.exceptions.AMQPConnectionError, tries=3, delay=5)
def connection_to_rabbit():
    rabbit = pika.BlockingConnection(pika.ConnectionParameters(HOST, PORT))
    channel = rabbit.channel()
    channel.queue_declare(queue='telegram')
    return channel


def callback(ch, method, properties, body):
    response_string = body.decode('utf-8')
    send_to_telegram(response_string)
    print(response_string)


def start_reading():
    channel = connection_to_rabbit()
    channel.basic_consume(queue='telegram', on_message_callback=callback, auto_ack=True)
    channel.basic_qos(prefetch_count=1)
    thread = Thread(target=channel.start_consuming)
    thread.start()

start_reading()

# channel.start_consuming()
# @app.before_request
# def restrict_access():
#     allowed_ips = ['0.0.0.0', '127.0.0.1']
#     remote_ip = request.remote_addr
#     if remote_ip not in allowed_ips:
#         abort(403)


@app.route("/mailagent", methods=["GET"])
def start():
    if request.method == "GET":
        return (make_response(jsonify("Im mail agent!"), 200))


@app.route('/metrics', methods=["GET"])
def metrics():
    value = service_metric._value.get()
    prometheus_metrics = generate_latest()
    combined_metrics = f'service_metric {value}\n{prometheus_metrics.decode("utf-8")}'
    return Response(combined_metrics, mimetype="text/plain")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8008, debug=True)
