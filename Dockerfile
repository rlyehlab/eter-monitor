FROM debian:9-slim

RUN apt-get update  && \
    apt-get install  python3-pip  -y
   
ADD  /src_api /src_api

WORKDIR   /src_api

RUN pip3 install -r /src_api/requirements.txt

EXPOSE 80

CMD ["python3", "src_api/run.py"]



