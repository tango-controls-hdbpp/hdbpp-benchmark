FROM nexus.engageska-portugal.pt/ska-docker/tango-pytango:latest

USER root

ARG TANGO_HOST
ENV PYTHONPATH="$PYTHONPATH:/usr/src/app"
ENV TANGO_HOST=${TANGO_HOST}

RUN mkdir -p /usr/src/app

#COPY ../../conf/hdbpp_evgen.conf /etc/hdb/hdbpp_evgen.conf

COPY ./script/hdbppconfig.py /usr/src/app/hdbppconfig.py

RUN chmod 755 /usr/src/app/hdbppconfig.py

# the config file should be mounted if the user wants to customise it
#CMD [ "/usr/src/app/hdbppconfig.py", "--device=archiving/hdbppmanager/0", "--archiver=archiving/hdbppsubscriber/0", "--file=/hdbpp_conf/hdbpp_evgen.conf" ]





