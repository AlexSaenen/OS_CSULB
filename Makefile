build:
	docker build -t linux_program .

destroy:
	docker rm -f OSTester
	docker rmi -f linux_program

run:
	docker run -d --name OSTester -t linux_program bash

go:
	docker exec -ti OSTester bash
