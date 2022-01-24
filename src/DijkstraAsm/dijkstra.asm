; J�ZYKI ASEMBLEROWE
; Projekt: Alogrytm Dijkstry
; Wyznacza najkr�tsz� tras� mi�dzy zadanymi miastami (wierzcho�kami grafu)
; Miko�aj Malich
; Rok akademicki 2021/2022

.data
varZero DQ 0 ; pomocnicza zmienna 0
; u�atwienie operacji na stosie
; zamiast np. QWORD PTR [rsp+32] w dalszej cz�ci kodu b�d� stosowa� QWORD PTR size$[rsp] 
v$ = 0 ; zmienna pomocnicza w p�tli(2)
j$ = 4 ; zmienna pomocnicza w p�tli(1)
x$ = 8 ; licznik odwiedzonych wierzcho�k�w
tail$ = 24 ; tymczasowy ko�cowy indeks
; przekazane do dll
size$ = 32 ; ilo�� wierzcho�kow
min$ = 40 ; minimalna odleglo��
tmp$ = 48 ; pomocnicza odleg�o�ci
dist$ = 56 ; tablica odleg�o�ci
visited$ = 64 ; tablica odwiedzonych wierzcho�k�w
u$ = 72 ; aktualnie rozpatrywany wierzcho�ek
graph$ = 80 ; tablica grafu
prev$ = 88 ; tablica poprzednik�w
;*******************************************************************************
.code
dijkstraPart proc 
        mov     QWORD PTR size$[rsp], r9
        mov     QWORD PTR tail$[rsp], r8
        mov     [rsp+16], rdx
        mov     QWORD PTR x$[rsp], rcx
        sub     rsp, 24
        mov     DWORD PTR x$[rsp], 0    ; int x = 0

; g��wna p�tla programu
        ; while (x != *size)
mainLoop:
        mov     rax, QWORD PTR size$[rsp]
        mov     eax, [rax]
        cmp     DWORD PTR x$[rsp], eax  ; por�wnanie
        je      exitMainLoop            ; skok przy niespe�nieniu warunku -> gdy x == size
        
        ; *min = *tmp;
        mov     rax, QWORD PTR min$[rsp]
        mov     rcx, QWORD PTR tmp$[rsp]
        movss   xmm0, DWORD PTR [rcx]   ; �adowanie warto�ci do xmm0
        movss   DWORD PTR [rax], xmm0

; pierwsza p�tla
        mov     DWORD PTR j$[rsp], 0 ; int j = 0
        jmp     findMinVertexLoop

; zwi�kszanie licznika pierwszej p�tli
incrementJ:
        mov     eax, DWORD PTR j$[rsp]
        inc     eax                    ; j++
        mov     DWORD PTR j$[rsp], eax

; pierwsza p�tla - szukanie wierzcho�ka o minimalnym koszcie doj�cia
findMinVertexLoop:
        mov     rax, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR j$[rsp], eax ; j < *size
        jge     secondLoopInitialization ; skok do dalszej cz�ci programu je�li j >= size

        ; if *(dist + j) <= *min
        movsxd  rax, DWORD PTR j$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR min$[rsp]
        mov     rdx, QWORD PTR dist$[rsp]
        movss   xmm0, DWORD PTR [rcx]
        comiss  xmm0, DWORD PTR [rdx+rax*4] ; por�wnanie (czy nowa odleg�o�� jest mniejsza) i ustawienie flag
        jb      findMinVertexLoopNextIteration ; skok przy niespe�nieniu warunku

        ; ci�g dalszy if:
        ; *(visited + j) != 1
        movsxd  rax, DWORD PTR j$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR visited$[rsp]
        cmp     DWORD PTR [rcx+rax*4], 1 ; por�wnanie -> czy wierzcho�ek odwiedzony
        je      findMinVertexLoopNextIteration ; skok je�li wierzcho�ek by� ju� rozpatrywany
        
        ; *u = j;
        mov     rax, QWORD PTR u$[rsp]
        mov     ecx, DWORD PTR j$[rsp]
        mov     DWORD PTR [rax], ecx ; nowe u

        ; *min = *(dist + j);
        movsxd  rax, DWORD PTR j$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR min$[rsp]
        mov     rdx, QWORD PTR dist$[rsp]
        movss   xmm0, DWORD PTR [rdx+rax*4] ; przypisanie z *(dist + j)
        movss   DWORD PTR [rcx], xmm0 ; nowe min

; skok do pocz�tku pierwszej p�tli
findMinVertexLoopNextIteration:
        jmp     incrementJ

; pocz�tek drugiej p�tli
secondLoopInitialization:
        mov     DWORD PTR v$[rsp], 0 ; int v = 0
        jmp     relaxationLoop

; zwi�kszanie licznika drugiej p�tli
incrementV:
        mov     eax, DWORD PTR v$[rsp]
        inc     eax                     ; v++
        mov     DWORD PTR v$[rsp], eax

; druga p�tla - relaksacja �uk�w grafu
relaxationLoop:
        mov     rax, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR v$[rsp], eax ; por�wnanie v i size
        jge     setVertexAsVisited ; skok w przypadku gdy v >= size

        ; if *(graph + *u * *size + v) > 0
        mov     rax, QWORD PTR u$[rsp]
        mov     rcx, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        imul    eax, DWORD PTR [rcx] ; mno�enie u * size
        cdqe    ; konwersja dword do qword (32 -> 64bit, int -> long)
                ; rozszerza EAX do RAX
        mov     rcx, QWORD PTR graph$[rsp]
        lea     rax, QWORD PTR [rcx+rax*8] ; bezpo�rednie sumowanie (graph + *u * *size)
        movsxd  rcx, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        movsd   xmm0, QWORD PTR [rax+rcx*8] ; dodanie do poprzedniego wyniku v
        comisd  xmm0, QWORD PTR varZero ; por�wnanie do 0 i ustawienie flag
        jbe     relaxationLoopNextIteration ; skok w przypadku niespe�nienia warunku (wynik <= 0)
        
        ; ci�g dalszy if:
        ; *(visited + v) != 1
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR visited$[rsp]
        cmp     DWORD PTR [rcx+rax*4], 1 ; por�wnanie czy wierzcho�ek odwiedzony
        je      relaxationLoopNextIteration ; skok je�li warunek niespe�niony (wierzcho�ek by� ju� rozpatrywany)
        
        ; relaksacja �uk�w grafu
        ; if *(dist + *u)
        mov     rax, QWORD PTR u$[rsp]
        movsxd  rax, DWORD PTR [rax] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR dist$[rsp]
        cvtss2sd xmm0, DWORD PTR [rcx+rax*4] ; konwersja (single -> double) i operacja przekazania do xmm0 wyniku dist + u
        
        ; ci�g dalszy if:
        ; *(graph + *u * *size + v)
        mov     rax, QWORD PTR u$[rsp]
        mov     rcx, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        imul    eax, DWORD PTR [rcx] ; mno�enie u * size
        cdqe    ; konwersja dword do qword (32 -> 64bit, int -> long)
                ; rozszerza EAX do RAX
        mov     rcx, QWORD PTR graph$[rsp]
        lea     rax, QWORD PTR [rcx+rax*8] ; bezpo�rednie sumowanie (graph + *u * *size)
        movsxd  rcx, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        addsd   xmm0, QWORD PTR [rax+rcx*8] ; dodanie v do wyniku i zawarto�ci xmm0
        
        ; ci�g dalszy if:
        ; *(dist + v)
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR dist$[rsp]
        cvtss2sd xmm1, DWORD PTR [rcx+rax*4] ; konwersja (single -> double) i operacja przekazania do xmm1 wyniku dist + v 
        comisd  xmm1, xmm0 ; porownanie zawarto�ci rejestr�w
        jbe     relaxationLoopNextIteration ; skok je�li warunek niespe�niony (�cie�ka doj�cia nieop�acalna)
        
        ; *(dist + v) = *(graph + *u * *size + v)
        mov     rax, QWORD PTR u$[rsp]
        mov     rcx, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        imul    eax, DWORD PTR [rcx] ; mno�enie u * size
        cdqe    ; konwersja dword do qword (32 -> 64bit, int -> long)
                ; rozszerza EAX do RAX
        mov     rcx, QWORD PTR graph$[rsp]
        lea     rax, QWORD PTR [rcx+rax*8] ; bezpo�rednie sumowanie (graph + *u * *size)
        movsxd  rcx, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        cvtsd2ss xmm0, QWORD PTR [rax+rcx*8] ; konwersja (double -> single) i przekazanie do xmm0 wyniku graph + *u * *size + v
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR dist$[rsp]
        movss   DWORD PTR [rcx+rax*4], xmm0 ; nowa warto�� w (dist + v) - odleg�o�ci do poprzedniego wierzcho�ka

        ; *(prev + v) = *u
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR prev$[rsp]
        mov     rdx, QWORD PTR u$[rsp]
        mov     edx, DWORD PTR [rdx]
        mov     DWORD PTR [rcx+rax*4], edx ; nowa warto�� - poprzednik danego wierzcho�ka

; skok do pocz�tku drugiej p�tli
relaxationLoopNextIteration:
        jmp     incrementV

; ustawienie statusu wierzcho�ka jako odwiedzony i inkrementacja licznika p�tli (liczby odwiedzonych wierzcho�k�w)
setVertexAsVisited:
        mov     rax, QWORD PTR u$[rsp]
        movsxd  rax, DWORD PTR [rax] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR visited$[rsp]
        mov     DWORD PTR [rcx+rax*4], 1 ; *(visited + *u) = 1
        mov     eax, DWORD PTR x$[rsp]
        inc     eax                      ; x++
        mov     DWORD PTR x$[rsp], eax
        jmp     mainLoop

; obs�uga ko�ca g��wnej p�tli
exitMainLoop:
        add     rsp, 24
        ret     0   ; powr�t z procedury

dijkstraPart endp
end