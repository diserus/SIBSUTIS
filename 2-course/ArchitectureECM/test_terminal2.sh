#!/bin/bash
ESC="\033"
CLEAR="${ESC}[2J"
GOTO="${ESC}[9;5H"
ENTER_ALT="${ESC}(0"
EXIT_ALT="${ESC}(B"
TL="l"  
TR="k" 
BL="m"  
BR="j"  
HLINE="q"
VLINE="x"
FILL="a"  
draw_box() {
    echo -ne "$GOTO"
    echo -ne "$ENTER_ALT"
    echo -ne "$TL"
    for ((i=1; i<=6; i++)); do echo -ne "$HLINE"; done
    echo -ne "$TR"
    for ((j=1; j<=6; j++)); do
        echo -ne "${ESC}[$((9+j));5H$VLINE      $VLINE"
    done
    echo -ne "${ESC}[15;5H$BL"
    for ((i=1; i<=6; i++)); do echo -ne "$HLINE"; done
    echo -ne "$BR"
    echo -ne "${ESC}[10;7H$FILL$FILL$FILL"
    echo -ne "${ESC}[11;9H$FILL"
    echo -ne "${ESC}[12;7H$FILL$FILL$FILL"
    echo -ne "${ESC}[13;9H$FILL"
    echo -ne "${ESC}[14;7H$FILL$FILL$FILL"
    echo -ne "$EXIT_ALT"
    echo
}
echo -ne "$CLEAR"
draw_box