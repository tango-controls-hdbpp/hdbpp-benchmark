NAME=hdbpp-test-insertion

default: image

build-files/.built: Dockerfile
	mkdir -p build-files/
	docker build -t $(NAME):latest .
	touch build-files/.built

lint:
	docker run --rm -i hadolint/hadolint < Dockerfile

build: image
image: build-files/.built

push: build-files/.built
# User must set this environment variable if they want to push the image to a docker repo
ifndef DOCKER_REGISTRY
	$(error DOCKER_REGISTRY is not set)
endif

	docker tag ${NAME}:latest ${DOCKER_REGISTRY}/${NAME}
	docker push ${DOCKER_REGISTRY}/${NAME}

clean:
	rm -fr build-files

.PHONY: default build image clean
