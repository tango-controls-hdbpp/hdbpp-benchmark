FROM nexus.engageska-portugal.pt/ska-docker/tango-pytango:latest

USER root

ARG TANGO_HOST
ENV PYTHONPATH="$PYTHONPATH:/usr/src/app"
ENV TANGO_HOST=${TANGO_HOST}

RUN python3 -m pip install docker

RUN mkdir -p /usr/src/app

COPY ./script/hdbpp-test-insertion.py /usr/src/app/hdbpp-test-insertion.py

RUN chmod 755 /usr/src/app/hdbpp-test-insertion.py

# the config file should be mounted if the user wants to customise it
#CMD [ "/usr/src/app/hdbpp-test-insertion.py", "-t", "long", "-s", "scalar", "-w", "ro", "-a", "archiving/hdbppsubscriber/0", "-e", "archiving/evgen/0", "-p", "100000", "-n", "1000" ]





