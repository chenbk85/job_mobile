PYTHON=/usr/bin/python26
PROTOC=/usr/local/bin/protoc


all: config.pyc presence.pyc presence_pb2.pyc protocol.pyc pserver.pyc


presence_pb2.pyc: ../src/protocol/presence.proto
	$(PROTOC) --proto_path=../src/protocol --python_out=./ \
				../src/protocol/presence.proto
	$(PYTHON) -c "import presence_pb2"

config.pyc: config.py
	$(PYTHON) -c "import config"

presence.pyc: presence.py
	$(PYTHON) -c "import presence"

protocol.pyc: protocol.py
	$(PYTHON) -c "import protocol"

pserver.pyc: pserver.py
	$(PYTHON) -c "import pserver"

clean:
	rm -f presence_pb2.py *.pyc
