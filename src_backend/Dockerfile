FROM python:3-slim

ADD . /app

WORKDIR /app

RUN pip install -r /app/requirements.txt

CMD ["python", "-u", "-B","run.py"]
