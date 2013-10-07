PROJECT=ip_intro
VERSION=1.1.1
TARDIR=$(PROJECT)-$(VERSION)
#Latex用コマンド
TEX=platex
#DVIのPDF化コマンド
DVI2PDF=dvipdfmx
#オプション
DVI2PDFOPTIONS =  # -f dlbase14.map

all: $(PROJECT).pdf

$(PROJECT).pdf:	$(PROJECT).dvi
	$(DVI2PDF) $(DVI2PDFOPTIONS) $(PROJECT).dvi

$(PROJECT).dvi: $(PROJECT).aux 
	(while grep "^LaTeX Warning: Label(s) may have changed." $(PROJECT).log; do $(TEX) $(PROJECT).tex; done)
$(PROJECT).aux: $(PROJECT).tex
	$(TEX) $(PROJECT)

clean-all : 
	rm -f $(PROJECT).pdf
	rm -f *.aux *.log *.dvi 
	rm -f *~
clean:
	rm -f *.aux *.log *.dvi 
	rm -f *~
