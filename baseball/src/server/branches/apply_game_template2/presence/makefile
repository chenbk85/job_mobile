PYTHON=/usr/bin/python
PROTOC=/usr/local/bin/protoc


all: config.pyc presence.pyc presence_pb2.pyc database.pyc protocol.pyc pserver.pyc

MSG_ROOT=../../MSG/

presence_pb2.pyc: $(MSG_ROOT)include/protocol/presence.proto
	$(PROTOC) --proto_path=$(MSG_ROOT)include/protocol --python_out=./ \
				$(MSG_ROOT)include/protocol/presence.proto
	$(PYTHON) -c "import presence_pb2"

config.pyc: config.py
	$(PYTHON) -c "import config"

presence.pyc: presence.py
	$(PYTHON) -c "import presence"

database.pyc: database.py
	$(PYTHON) -c "import database"

protocol.pyc: protocol.py
	$(PYTHON) -c "import protocol"

pserver.pyc: pserver.py
	$(PYTHON) -c "import pserver"

clean:
	rm -f presence_pb2.py *.pyc
