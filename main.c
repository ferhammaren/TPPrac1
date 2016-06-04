/*
 * File:   main.c
 * Author: Ferhammaren
 *
 * Created on den 26 augusti 2014, 12:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/*
 *
 */
int main(int argc, char** argv) {
    int sw, codigo[100], existencia[100], cod, count = 0, a, b, found = 0, ex = 1, c = 1;
    float precio[100], pre;
    char descripcion[100][50], descr[50], g;
    initscr();

    do {
        erase();
        refresh();
        mvprintw(2, 25, "MUNDO DE CARAMELO");
        mvprintw(4, 25, "[1]Altas");
        mvprintw(5, 25, "[2]Consulta por Precio");
        mvprintw(6, 25, "[3]Modificaciones");
        mvprintw(7, 25, "[4]Consulta por descripción");
        mvprintw(8, 25, "[5]Terminar\n");
        refresh();
        scanw("%d", &sw);
        switch (sw) {
            case 1:
                // <editor-fold defaultstate="collapsed" desc="Altas">
                do {
                    found = 0;
                    erase();
                    refresh();
                    mvprintw(2, 25, "ALTAS");
                    mvprintw(4, 10, "Ingresa el código de barras: ");
                    refresh();
                    scanw("%d", &cod);
                    if (count > 0) {//la variable count, que contiene el numero de elementos en los arreglos
                        for (a = 0; a < count; a++) {//recorre el arreglo de codigos
                            if (cod == codigo[a]) {//compara el codigo capturado a los que ya hay
                                found = 1;
                            }
                        }
                        if (found != 0) {
                            mvprintw(5, 10, "ERROR: Código duplicado");
                            getch();
                            refresh();
                        } else { //si no se encuentra el codigo entonces se guarda y se incrementa count
                            codigo[count] = cod;
                        }
                    } else {
                        codigo[count] = cod;
                    }
                } while (found != 0);
                do {
                    found = 0;
                    mvprintw(5, 10, "Ingresa la descripción: ");
                    refresh();
                    getstr(descr);
                    if (count > 0) {
                        for (a = 0; a < count; a++) {
                            if (strcasecmp(descr, descripcion[a]) == 0) {
                                found = 1;
                            }
                        }
                        if (found != 0) {
                            mvprintw(5, 10, "ERROR: Nombre duplicado");
                            refresh();
                            getch();
                        } else {
                            strcpy(descripcion[count], descr);
                        }
                    } else {
                        strcpy(descripcion[count], descr);
                    }
                } while (found != 0);
                do {
                    mvprintw(6, 10, "Ingresa la existencia del producto: ");
                    refresh();
                    scanw("%d", &ex);
                    if (ex < 1) {
                        mvprintw(6, 46, "ERROR: Ingresa un número mayor a 0");
                        refresh();
                        getch();
                    }
                    mvprintw(6, 50, "                                 ");
                    refresh();
                } while (ex < 1);
                existencia[count] = ex;
                mvprintw(7, 10, "Ingresa el precio del producto: ");
                scanw("%f", &precio[count]);
                count++;
                printw("||%d||", count);
                refresh();
                getch();
                break;
                // </editor-fold>
            case 2:
                // <editor-fold defaultstate="collapsed" desc="Consulta por Precio">
                erase();
                refresh();
                if (count < 1) {
                    mvprintw(2, 25, "ERROR: No hay productos capturados");
                    refresh();
                    getch();
                } else {
                    // <editor-fold defaultstate="collapsed" desc="ordenacion">
                    for (a = 0; a < count - 1; a++) {//ordena el arreglo por precio
                        for (b = a + 1; b < count; b++) {
                            if (precio[a] > precio[b]) {
                                cod = codigo[a];
                                strcpy(descr, descripcion[a]);
                                pre = precio[a];
                                ex = existencia[a];
                                codigo[a] = codigo[b];
                                strcpy(descripcion[a], descripcion[b]);
                                precio[a] = precio[b];
                                existencia[a] = existencia[b];
                                codigo[b] = cod;
                                strcpy(descripcion[b], descr);
                                precio[b] = pre;
                                existencia[b] = ex;
                            }
                        }
                    }//termina ordenacion// </editor-fold>
                    mvprintw(2, 25, "CONSULTA ORDENADA POR PRECIO");
                    mvprintw(4, 1, "Código de barras");
                    mvprintw(4, 17, "Descripción");
                    mvprintw(4, 67, "Existencias");
                    mvprintw(4, 79, "Precio");
                    refresh();
                    for (a = 0; a < count; a++) {
                        mvprintw(5 + a, 1, "%d", codigo[a]);
                        mvprintw(5 + a, 17, "%s", descripcion[a]);
                        mvprintw(5 + a, 67, "%d", existencia[a]);
                        mvprintw(5 + a, 79, "%.2f", precio[a]);
                        refresh();
                    }
                }
                getch();
                break;
                // </editor-fold>
            case 3:
                // <editor-fold defaultstate="collapsed" desc="Modificaciones por codigo de barras">
                erase();
                refresh();
                mvprintw(2, 25, "Modificaciones por codigo de barras");
                if (count < 1) {
                    mvprintw(3, 5, "ERROR: No hay productos capturados");
                } else {
                    mvprintw(3, 5, "Ingresa el código de barras del producto a modificar: ");
                    scanw("%d", &cod);
                    a = 0;
                    for (b = 0; b < count; b++) {
                        if (codigo[b] == cod) {
                            a = 1;
                            found = b;
                        }
                    }
                    if (a != 1) {
                        mvprintw(4, 5, "ERROR: No se encontró el producto");
                    } else {
                        do {
                            erase();
                            refresh();
                            mvprintw(2, 25, "Modificaciones por código de barras");
                            mvprintw(4, 5, "[1]Modificar descripción");
                            mvprintw(5, 5, "[2]Modificar existencia");
                            mvprintw(6, 5, "[3]Modificar precio");
                            mvprintw(7, 5, "[4]Regresar");
                            refresh();
                            scanw("%d", &c);
                            switch (c) {
                                case 1:
                                    erase();
                                    refresh();
                                    do {
                                        c = 0;
                                        mvprintw(2, 2, "Ingresa la nueva descripción: ");
                                        refresh();
                                        getstr(descr);
                                        if (count > 0) {
                                            for (a = 0; a < count; a++) {
                                                if (strcasecmp(descr, descripcion[a]) == 0) {
                                                    c = 1;
                                                }
                                            }
                                            if (c != 0) {
                                                mvprintw(5, 10, "ERROR: Nombre duplicado");
                                                refresh();
                                                getch();
                                            } else {
                                                strcpy(descripcion[found], descr);
                                            }
                                        } else {
                                            strcpy(descripcion[found], descr);
                                        }
                                    } while (c != 0);
                                    break;
                                case 2:
                                    erase();
                                    refresh();
                                    mvprintw(2, 2, "Ingresa la existencia del producto: ");
                                    refresh();
                                    scanw("%d", &ex);
                                    if (ex < 1) {
                                        for (a = found; a < count - 1; a++) {
                                            codigo[a] = codigo[a + 1];
                                            strcpy(descripcion[a], descripcion[a + 1]);
                                            existencia[a] = existencia[a + 1];
                                            precio[a] = precio[a + 1];

                                        }
                                        count--;
                                        mvprintw(3, 2, "Se ha eliminado el producto");
                                        refresh();
                                        getch();
                                    } else {
                                        existencia[found] = ex;
                                    }
                                    break;
                                case 3:
                                    erase();
                                    refresh();
                                    mvprintw(2, 2, "Ingresa el nuevo precio: ");
                                    refresh();
                                    scanw("%f", &precio[found]);
                                    break;
                                case 4:
                                    break;
                                default:
                                    erase();
                                    refresh();
                                    mvprintw(2, 5, "ERROR: No existe esa opción");
                                    break;
                            }

                        } while (c != 4);
                    }
                }
                break;
                // </editor-fold>
            case 4:
                // <editor-fold defaultstate="collapsed" desc="Consulta por nombre/descripcion">
                b = 0;
                erase();
                refresh();
                mvprintw(2, 15, "Consulta por descripción");
                if (count < 1) {
                    mvprintw(3, 5, "ERROR:No hay productos capturados");
                    refresh();
                } else {
                    mvprintw(3, 5, "Ingresa el nombre del producto: ");
                    refresh();
                    getstr(descr);
                    for (a = 0; a < count; a++) {
                        if (strcasecmp(descripcion[a], descr) == 0) {
                            b = 1;
                            found = a;
                        }
                    }
                    if (b != 1) {
                        mvprintw(4, 5, "ERROR: No se encontró el producto");
                        refresh();
                        getch();
                    } else {
                        mvprintw(4, 1, "Código de barras");
                        mvprintw(4, 18, "Descripción");
                        mvprintw(4, 67, "Existencias");
                        mvprintw(4, 79, "Precio");
                        mvprintw(5, 1, "%d", codigo[found]);
                        mvprintw(5, 17, "%s", descripcion[found]);
                        mvprintw(5, 67, "%d", existencia[found]);
                        mvprintw(5, 79, "%.2f", precio[found]);
                        refresh();
                        getch();
                    }
                }
                break;
                // </editor-fold>
            case 5:
                erase();
                refresh();
                break;
            default:
                erase();
                refresh();
                mvprintw(2, 10, "ERROR:No existe esa opción");
                refresh();
                getch();
                break;
        }
    } while (sw != 5);
    endwin();
    return 0;
}

