JAVADIR=/usr/share/java
PROJDIR=/home/oops/project/
CLASSPATH=$JAVADIR/po-uilib.jar:$JAVADIR/edt-support.jar:$PROJDIR/edt-textui/edt-textui.jar:$PROJDIR/edt-core/edt-core.jar
echo $CLASSPATH
java -Dimport=project/edt-textui/test.import -cp $CLASSPATH edt.textui.TextEditor