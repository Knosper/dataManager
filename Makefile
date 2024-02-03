NAME := DataController

ENV_FILE := .env
include $(ENV_FILE)

# Get the host UID dynamically
HOST_UID := $(shell id -u)

VOLUMES := $(BACKEND_VOLUME) $(FRONTEND_VOLUME)

DOCKER_COMPOSE := docker compose --env-file=$(ENV_FILE) 

all: build

$(VOLUMES):
	mkdir -p $(VOLUMES)

build: | $(VOLUMES)
	USER=$(HOST_UID) $(DOCKER_COMPOSE) up --build

clean:
	$(DOCKER_COMPOSE) down

fclean:
	$(DOCKER_COMPOSE) down --rmi=all --volumes

re: clean
	make all

.PHONY: all build clean fclean re


config:
	$(DOCKER_COMPOSE) config --format=json | jq

prune:
	docker system prune --all --force --volumes
	-docker network rm $$(docker network ls -q)
	-docker volume  rm $$(docker volume  ls -q)

.PHONY: config prune