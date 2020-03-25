# Produce PDFs from all Markdown files in a directory
# Lincoln Mullen | http://lincolnmullen.com | lincoln@lincolnmullen.com

## Markdown Template
TEMP-PWD = /home/corsi/tmp/Corsi-Pandoc-Class-Handout
TEMP-TEXT = $(TEMP-PWD)/InsperTemplate.tex
TEMP-SLIDE = $(TEMP-PWD)/InsperTemplateSlide.tex
TEMP-FILTER = $(TEMP-PWD)/filterBox.py
HEADER = $(TEMP-PWD)/cabecalho.png
LOGO = $(TEMP-PWD)/logo.pdf

## SRC
FILE-LISTA = 07-Lista-PIO-Irq
FILE-HANDOUT = 07-Handout-PIO-Irq

all : HANDOUT LISTA

HANDOUT:	$(FILE-HANDOUT).md
	pandoc $< --template=$(TEMP-TEXT) --variable logo=$(LOGO) --variable header=$(HEADER) -f markdown --filter pandoc-latex-tip --filter $(TEMP-FILTER) --pdf-engine=xelatex	-o $(FILE-HANDOUT).pdf

TEX:	$(FILE-HANDOUT).md
	pandoc $< --template=$(TEMP-TEXT) --variable logo=$(LOGO) --variable header=$(HEADER) -f markdown --filter pandoc-latex-tip --filter $(TEMP-FILTER) --pdf-engine=xelatex	-o $(FILE-HANDOUT).tex


LISTA:	$(FILE-LISTA).md
	pandoc $< --template=$(TEMP-TEXT) --variable logo=$(LOGO) --variable header=$(HEADER) -f markdown --filter pandoc-latex-tip --filter $(TEMP-FILTER) --pdf-engine=xelatex	-o $(FILE-LISTA).pdf


SLIDES: $(FILE-SLIDE).md
	pandoc $< --to=beamer -V theme:metropolis --variable logo=$(LOGO-PNG) --variable header=$(HEADER) -f markdown --slide-level 2 --pdf-engine=xelatex  -fmarkdown-implicit_figures -o $(FILE-SLIDE).pdf
