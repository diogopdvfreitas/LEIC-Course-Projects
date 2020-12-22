JAVADIR=/usr/share/java
JARNAME=edt-textui

all:
	(cd src; javac -encoding UTF-8 -cp $(JAVADIR)/po-uilib.jar:$(JAVADIR)/edt-support.jar:../../edt-core/edt-core.jar `find . -name \*.java`)
	(cd src; jar cvf ../$(JARNAME).jar `find . -name \*.class -o -name \*.java`)

clean:
	$(RM) $(JARNAME).jar `find . -name \*.class`

install:
	/bin/cp $(JARNAME).jar $(JAVADIR)
