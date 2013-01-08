http://www.codeproject.com/KB/system/mctutorial.aspx


jServerTestEvent.mc 의 컴파일 명령.

mc -U $(InputName).mc
 rc -r $(InputName).rc
 link -dll -noentry -out:$(BIN)\$(InputName).dll $(InputName).res
 
 
 jServerTestEvent.mc의 출력명령.
 $(InputDir)\$(InputName).h