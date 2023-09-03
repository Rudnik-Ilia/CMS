FROM python:3.8-slim

WORKDIR /app

COPY requirements.txt .

RUN pip install -r requirements.txt

COPY . /app

EXPOSE 8000

ENV NAME World

CMD ["flask", "db", "init"]
CMD ["flask", "db", "migrate", "-m", "'Create table'"]
CMD ["flask", "db", "upgrate"]


CMD ["python", "wsgi.py"]