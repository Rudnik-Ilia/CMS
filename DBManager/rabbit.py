import pika
from pika import exceptions


def rabbit_connect_add(message: str, queue: str = "telegram", host: str = "rabbitmq", port: int = 5672):
    try:
        rabbit = pika.BlockingConnection(pika.ConnectionParameters(host=host, port=port))
    except pika.exceptions.AMQPConnectionError as exc:
        print("Failed to connect to RabbitMQ service. Message wont be sent.", exc)
        return
    channel = rabbit.channel()
    channel.queue_declare(queue=queue)
    channel.basic_publish(exchange='', routing_key='telegram', body=bytes(message, 'utf-8'))
    rabbit.close()


