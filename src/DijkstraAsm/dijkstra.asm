; JÊZYKI ASEMBLEROWE
; Projekt: Alogrytm Dijkstry
; Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
; Miko³aj Malich
; Rok akademicki 2021/2022

.data
varZero DQ 0 ; pomocnicza zmienna 0
; u³atwienie operacji na stosie
; zamiast np. QWORD PTR [rsp+32] w dalszej czêœci kodu bêdê stosowa³ QWORD PTR size$[rsp] 
v$ = 0 ; zmienna pomocnicza w pêtli(2)
j$ = 4 ; zmienna pomocnicza w pêtli(1)
x$ = 8 ; licznik odwiedzonych wierzcho³ków
tail$ = 24 ; tymczasowy koñcowy indeks
; przekazane do dll
size$ = 32 ; iloœæ wierzcho³kow
min$ = 40 ; minimalna odlegloœæ
tmp$ = 48 ; pomocnicza odleg³oœci
dist$ = 56 ; tablica odleg³oœci
visited$ = 64 ; tablica odwiedzonych wierzcho³ków
u$ = 72 ; aktualnie rozpatrywany wierzcho³ek
graph$ = 80 ; tablica grafu
prev$ = 88 ; tablica poprzedników
;*******************************************************************************
.code
dijkstraPart proc 
        mov     QWORD PTR size$[rsp], r9
        mov     QWORD PTR tail$[rsp], r8
        mov     [rsp+16], rdx
        mov     QWORD PTR x$[rsp], rcx
        sub     rsp, 24
        mov     DWORD PTR x$[rsp], 0    ; int x = 0

; g³ówna pêtla programu
        ; while (x != *size)
mainLoop:
        mov     rax, QWORD PTR size$[rsp]
        mov     eax, [rax]
        cmp     DWORD PTR x$[rsp], eax  ; porównanie
        je      exitMainLoop            ; skok przy niespe³nieniu warunku -> gdy x == size
        
        ; *min = *tmp;
        mov     rax, QWORD PTR min$[rsp]
        mov     rcx, QWORD PTR tmp$[rsp]
        movss   xmm0, DWORD PTR [rcx]   ; ³adowanie wartoœci do xmm0
        movss   DWORD PTR [rax], xmm0

; pierwsza pêtla
        mov     DWORD PTR j$[rsp], 0 ; int j = 0
        jmp     findMinVertexLoop

; zwiêkszanie licznika pierwszej pêtli
incrementJ:
        mov     eax, DWORD PTR j$[rsp]
        inc     eax                    ; j++
        mov     DWORD PTR j$[rsp], eax

; pierwsza pêtla - szukanie wierzcho³ka o minimalnym koszcie dojœcia
findMinVertexLoop:
        mov     rax, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR j$[rsp], eax ; j < *size
        jge     secondLoopInitialization ; skok do dalszej czêœci programu jeœli j >= size

        ; if *(dist + j) <= *min
        movsxd  rax, DWORD PTR j$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR min$[rsp]
        mov     rdx, QWORD PTR dist$[rsp]
        movss   xmm0, DWORD PTR [rcx]
        comiss  xmm0, DWORD PTR [rdx+rax*4] ; porównanie (czy nowa odleg³oœæ jest mniejsza) i ustawienie flag
        jb      findMinVertexLoopNextIteration ; skok przy niespe³nieniu warunku

        ; ci¹g dalszy if:
        ; *(visited + j) != 1
        movsxd  rax, DWORD PTR j$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR visited$[rsp]
        cmp     DWORD PTR [rcx+rax*4], 1 ; porównanie -> czy wierzcho³ek odwiedzony
        je      findMinVertexLoopNextIteration ; skok jeœli wierzcho³ek by³ ju¿ rozpatrywany
        
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

; skok do pocz¹tku pierwszej pêtli
findMinVertexLoopNextIteration:
        jmp     incrementJ

; pocz¹tek drugiej pêtli
secondLoopInitialization:
        mov     DWORD PTR v$[rsp], 0 ; int v = 0
        jmp     relaxationLoop

; zwiêkszanie licznika drugiej pêtli
incrementV:
        mov     eax, DWORD PTR v$[rsp]
        inc     eax                     ; v++
        mov     DWORD PTR v$[rsp], eax

; druga pêtla - relaksacja ³uków grafu
relaxationLoop:
        mov     rax, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR v$[rsp], eax ; porównanie v i size
        jge     setVertexAsVisited ; skok w przypadku gdy v >= size

        ; if *(graph + *u * *size + v) > 0
        mov     rax, QWORD PTR u$[rsp]
        mov     rcx, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        imul    eax, DWORD PTR [rcx] ; mno¿enie u * size
        cdqe    ; konwersja dword do qword (32 -> 64bit, int -> long)
                ; rozszerza EAX do RAX
        mov     rcx, QWORD PTR graph$[rsp]
        lea     rax, QWORD PTR [rcx+rax*8] ; bezpoœrednie sumowanie (graph + *u * *size)
        movsxd  rcx, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        movsd   xmm0, QWORD PTR [rax+rcx*8] ; dodanie do poprzedniego wyniku v
        comisd  xmm0, QWORD PTR varZero ; porównanie do 0 i ustawienie flag
        jbe     relaxationLoopNextIteration ; skok w przypadku niespe³nienia warunku (wynik <= 0)
        
        ; ci¹g dalszy if:
        ; *(visited + v) != 1
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR visited$[rsp]
        cmp     DWORD PTR [rcx+rax*4], 1 ; porównanie czy wierzcho³ek odwiedzony
        je      relaxationLoopNextIteration ; skok jeœli warunek niespe³niony (wierzcho³ek by³ ju¿ rozpatrywany)
        
        ; relaksacja ³uków grafu
        ; if *(dist + *u)
        mov     rax, QWORD PTR u$[rsp]
        movsxd  rax, DWORD PTR [rax] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR dist$[rsp]
        cvtss2sd xmm0, DWORD PTR [rcx+rax*4] ; konwersja (single -> double) i operacja przekazania do xmm0 wyniku dist + u
        
        ; ci¹g dalszy if:
        ; *(graph + *u * *size + v)
        mov     rax, QWORD PTR u$[rsp]
        mov     rcx, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        imul    eax, DWORD PTR [rcx] ; mno¿enie u * size
        cdqe    ; konwersja dword do qword (32 -> 64bit, int -> long)
                ; rozszerza EAX do RAX
        mov     rcx, QWORD PTR graph$[rsp]
        lea     rax, QWORD PTR [rcx+rax*8] ; bezpoœrednie sumowanie (graph + *u * *size)
        movsxd  rcx, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        addsd   xmm0, QWORD PTR [rax+rcx*8] ; dodanie v do wyniku i zawartoœci xmm0
        
        ; ci¹g dalszy if:
        ; *(dist + v)
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR dist$[rsp]
        cvtss2sd xmm1, DWORD PTR [rcx+rax*4] ; konwersja (single -> double) i operacja przekazania do xmm1 wyniku dist + v 
        comisd  xmm1, xmm0 ; porownanie zawartoœci rejestrów
        jbe     relaxationLoopNextIteration ; skok jeœli warunek niespe³niony (œcie¿ka dojœcia nieop³acalna)
        
        ; *(dist + v) = *(graph + *u * *size + v)
        mov     rax, QWORD PTR u$[rsp]
        mov     rcx, QWORD PTR size$[rsp]
        mov     eax, DWORD PTR [rax]
        imul    eax, DWORD PTR [rcx] ; mno¿enie u * size
        cdqe    ; konwersja dword do qword (32 -> 64bit, int -> long)
                ; rozszerza EAX do RAX
        mov     rcx, QWORD PTR graph$[rsp]
        lea     rax, QWORD PTR [rcx+rax*8] ; bezpoœrednie sumowanie (graph + *u * *size)
        movsxd  rcx, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        cvtsd2ss xmm0, QWORD PTR [rax+rcx*8] ; konwersja (double -> single) i przekazanie do xmm0 wyniku graph + *u * *size + v
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR dist$[rsp]
        movss   DWORD PTR [rcx+rax*4], xmm0 ; nowa wartoœæ w (dist + v) - odleg³oœci do poprzedniego wierzcho³ka

        ; *(prev + v) = *u
        movsxd  rax, DWORD PTR v$[rsp] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR prev$[rsp]
        mov     rdx, QWORD PTR u$[rsp]
        mov     edx, DWORD PTR [rdx]
        mov     DWORD PTR [rcx+rax*4], edx ; nowa wartoœæ - poprzednik danego wierzcho³ka

; skok do pocz¹tku drugiej pêtli
relaxationLoopNextIteration:
        jmp     incrementV

; ustawienie statusu wierzcho³ka jako odwiedzony i inkrementacja licznika pêtli (liczby odwiedzonych wierzcho³ków)
setVertexAsVisited:
        mov     rax, QWORD PTR u$[rsp]
        movsxd  rax, DWORD PTR [rax] ; przeniesienie z rozszerzeniem
        mov     rcx, QWORD PTR visited$[rsp]
        mov     DWORD PTR [rcx+rax*4], 1 ; *(visited + *u) = 1
        mov     eax, DWORD PTR x$[rsp]
        inc     eax                      ; x++
        mov     DWORD PTR x$[rsp], eax
        jmp     mainLoop

; obs³uga koñca g³ównej pêtli
exitMainLoop:
        add     rsp, 24
        ret     0   ; powrót z procedury

dijkstraPart endp
end