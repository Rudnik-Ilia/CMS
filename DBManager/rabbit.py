import pika
from pika import exceptions


def rabbit_connect_add(message: str, queue: str = "telegram", host: str = "localhost"):
    try:
        rabbit = pika.BlockingConnection(pika.ConnectionParameters(host=host))
    except pika.exceptions.AMQPConnectionError as exc:
        print("Failed to connect to RabbitMQ service. Message wont be sent.", exc)
        return
    channel = rabbit.channel()
    channel.queue_declare(queue=queue)
    channel.basic_publish(exchange='', routing_key='hello', body=bytes(message, 'utf-8'))
    rabbit.close()


