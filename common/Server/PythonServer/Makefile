PYTHON=/usr/bin/python
PROTOC=/usr/local/bin/protoc --proto_path=./ --python_out=./

all: presence

gameLogic.proto: ../../protobuf/gameGostop.proto
	cp -f ../../protobuf/gameGoStop.proto ./gameLogic.proto

presence.proto: ../../protobuf/presence.proto
	cp -f ../../protobuf/presence.proto ./

game.proto: ../../protobuf/game.proto
	cp -f ../../protobuf/game.proto ./

ug.proto: ../../protobuf/ug.proto
	cp -f ../../protobuf/ug.proto ./

db.proto: ../../protobuf/db.proto
	cp -f ../../protobuf/db.proto ./



presence_pb2.pyc: presence.proto
	$(PROTOC) presence.proto
	$(PYTHON) -c "import presence_pb2"

gameLogic_pb2.pyc: gameLogic.proto
	$(PROTOC) gameLogic.proto
	$(PYTHON) -c "import gameLogic_pb2"

game_pb2.pyc: game.proto
	$(PROTOC) game.proto
	$(PYTHON) -c "import game_pb2"

ug_pb2.pyc: ug.proto
	$(PROTOC) ug.proto
	$(PYTHON) -c "import ug_pb2"

db_pb2.pyc: db.proto
	$(PROTOC) db.proto
	$(PYTHON) -c "import db_pb2"


presence.pyc: presence.py
	$(PYTHON) -c "import presence"

database.pyc: database.py
	$(PYTHON) -c "import database"

protocol.pyc: protocol.py
	$(PYTHON) -c "import protocol"

ug.pyc: ug.py
	$(PYTHON) -c "import ug"


presence: \
  gameLogic_pb2.pyc \
	db_pb2.pyc \
	presence_pb2.pyc \
	game_pb2.pyc \
	db_pb2.pyc \
	ug_pb2.pyc \
  presence.pyc \
  database.pyc \
  protocol.pyc \
	pserver.py

	$(PYTHON) -c "import pserver"

gateway: \
  gameLogic_pb2.pyc \
	db_pb2.pyc \
	presence_pb2.pyc \
	game_pb2.pyc \
	ug_pb2.pyc \
  ug.pyc \
  database.pyc \
  protocol.pyc \
	ugparent.py

	$(PYTHON) -c "import ugparent"



clean:
	rm -f *.proto *_pb2.py *.pyc 

