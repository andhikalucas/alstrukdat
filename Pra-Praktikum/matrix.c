#include <stdio.h>
#include "matrix.h"
/* Ukuran maksimum baris dan kolom */
// #define ROW_CAP 100
// #define COL_CAP 100

// typedef int IdxType; /* Index baris, kolom */
// typedef int ElType;
/*typedef struct
{
   ElType mem[ROW_CAP][COL_CAP];
   int rowEff; banyaknya/ukuran baris yg terdefinisi 
   int colEff; banyaknya/ukuran kolom yg terdefinisi 
} Matrix;
*/

/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor *** */
//#define ROW_EFF(M) (M).rowEff
//#define COL_EFF(M) (M).colEff
//#define ELMT(M, i, j) (M).mem[(i)][(j)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m){
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j){
    return (i >= 0 && j >= 0 && i < ROW_CAP && j < COL_CAP);
}
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m){
    return ROW_EFF(m) - 1;
}
/* Mengirimkan Index baris terbesar m */
IdxType getLastIdxCol(Matrix m){
    return COL_EFF(m) - 1;
}
/* Mengirimkan Index kolom terbesar m */
boolean isIdxEff(Matrix m, IdxType i, IdxType j){
    return (i >= 0 && j >= 0 && i < ROW_EFF(m) && j < COL_EFF(m));
}
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
ElType getElmtDiagonal(Matrix m, IdxType i){
    return ELMT(m, i, i);
}
/* Mengirimkan elemen m(i,i) */

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut){
    createMatrix(ROW_EFF(mIn), COL_EFF(mIn), mOut);
    for (int i = 0; i <= getLastIdxRow(mIn); i++){
        for (int j = 0; j <= getLastIdxCol(mIn); j++){
            ELMT(*mOut, i, j) = ELMT(mIn, i, j);
        }
    }
}
/* Melakukan assignment mOut <- mIn */

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol){
    createMatrix(nRow, nCol, m);
    for (int i = 0; i <= getLastIdxRow(*m); i++){
        for (int j = 0; j <= getLastIdxCol(*m); j++){
            scanf("%d", &ELMT(*m, i, j));
        }
    }

}
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void displayMatrix(Matrix m){
    for (int i = 0; i <= getLastIdxRow(m); i++){
        for (int j = 0; j <= getLastIdxCol(m); j++){
            printf("%d", ELMT(m,i,j));
            if (j < getLastIdxCol(m)){
                printf(" ");
            }
        }
        if (i != getLastIdxRow(m)){
            printf("\n");
        }
    }
}

/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2){
    for (int i = 0; i <= getLastIdxRow(m1); i++){
        for (int j = 0; j <= getLastIdxCol(m1); j++){
            ELMT(m1,i,j) += ELMT(m2,i,j);
        }
    }
    return m1;
}
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
Matrix subtractMatrix(Matrix m1, Matrix m2){
    for (int i = 0; i <= getLastIdxRow(m1); i++){
        for (int j = 0; j <= getLastIdxCol(m1); j++){
            ELMT(m1,i,j) -= ELMT(m2,i,j);
        }
    }
    return m1;
}
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
Matrix multiplyMatrix(Matrix m1, Matrix m2){
    Matrix m;
    createMatrix(ROW_EFF(m1), COL_EFF(m2), &m);
    for (int i = 0; i <= getLastIdxRow(m); i++){
        for (int j = 0; j <= getLastIdxCol(m); j++){
            for (int k = 0; k <= getLastIdxCol(m1); k++){
                ELMT(m,i,j) += ELMT(m1,i,k) * ELMT(m2, k, j);
            }
        }
    }
    return m;
}
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
Matrix multiplyByConst(Matrix m, ElType x){
    for (int i = 0; i <= getLastIdxRow(m); i++){
        for (int j = 0; j <= getLastIdxCol(m); j++){
            ELMT(m,i,j) = ELMT(m,i,j) * x;
        }
    }
    return m;
}
/* Mengirim hasil perkalian setiap elemen m dengan x */
void pMultiplyByConst(Matrix *m, ElType k){
    for (int i = 0; i <= getLastIdxRow(*m); i++){
        for (int j = 0; j <= getLastIdxCol(*m); j++){
            ELMT(*m,i,j) = ELMT(*m,i,j) * k;
        }
    }
}
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2){
    if (ROW_EFF(m1) != ROW_EFF(m2) || COL_EFF(m1) != COL_EFF(m2)){
        return false;
    }
    else{
        for (int i = 0; i <= getLastIdxRow(m1); i++){
            for (int j = 0; j <= getLastIdxCol(m2); j++){
                if (ELMT(m1,i,j) != ELMT(m2,i,j)){
                    return false;
                }
            }
        }
        return true;
    }
}
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
boolean isMatrixNotEqual(Matrix m1, Matrix m2){
    return (!isMatrixEqual(m1,m2));
}
/* Mengirimkan true jika m1 tidak sama dengan m2 */
boolean isMatrixSizeEqual(Matrix m1, Matrix m2){
    return (ROW_EFF(m1) == ROW_EFF(m2) && COL_EFF(m1) == COL_EFF(m2));
}
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
/* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */

/* ********** Operasi lain ********** */
int countElmt(Matrix m){
    return (COL_EFF(m) * ROW_EFF(m));
}
/* Mengirimkan banyaknya elemen m */

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m){
    return (COL_EFF(m) == ROW_EFF(m));
}
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSymmetric(Matrix m){
    if (!isSquare(m)){
        return false;
    }
    for (int i = 0; i <= getLastIdxRow(m); i++){
        for (int j = 0; j <= getLastIdxCol(m); j++){
            if (ELMT(m,i,j) != ELMT(m,j,i)){
                return false;
            }
        }
    }
    return true;
}
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
boolean isIdentity(Matrix m){
    if (!isSquare(m)){
        return false;
    }
    for (int i = 0; i <= getLastIdxRow(m); i++){
        for (int j = 0; j <= getLastIdxCol(m); j++){
            // Cek diagonal utama
            if (i == j){
                if (ELMT(m,i,j) != 1){
                    return false;
                }
            }
            else{
                if (ELMT(m,i,j) != 0){
                    return false;
                }
            }
            
        }
    }
    return true;
}
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
boolean isSparse(Matrix m){
    int count = 0;
    for (int i = 0; i <= getLastIdxRow(m); i++){
        for (int j = 0; j <= getLastIdxCol(m); j++){
            if (ELMT(m,i,j) != 0) count++;
        }
    }
    return (count <= (0.05) * (float)countElmt(m));
}
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
Matrix negation(Matrix m){
    return multiplyByConst(m,-1);
}
/* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
void pNegation(Matrix *m){
    pMultiplyByConst(m, -1);
}
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
float determinant(Matrix m){
    if (ROW_EFF(m) == 0) return (float)(0);
    if (ROW_EFF(m) == 1) return (float)(ELMT(m,0,0));
    if (ROW_EFF(m) == 2) return (float)((ELMT(m,0,0)*ELMT(m,1,1)) - (ELMT(m,0,1)*ELMT(m,1,0)));

    int rowMatrix, colMatrix, rowCo, colCo;
    float det = 0;

    // Iterate the row of Matrix to create a new Cofactor
    for (rowMatrix = 0; rowMatrix < ROW_EFF(m); rowMatrix++){
        Matrix Co;
        createMatrix(ROW_EFF(m)-1, COL_EFF(m)-1, &Co); // Create a new Co matrix which has 1 less row and col
        
        // Loop to fill the Co matrix by first iterating the row of Co
        for(rowCo = 0; rowCo < ROW_EFF(Co); rowCo++){
            int colCo = 0;
            // Copy the Matrix element to Co. Skip the rowMatrix elements.
            for(colMatrix = 0; colMatrix < COL_EFF(m); colMatrix++){ //Iteration has to start with Matrix so we can skip the i row/col
                if(colMatrix != rowMatrix){
                    ELMT(Co,rowCo,colCo) = ELMT(m,rowCo+1,colMatrix);
                    colCo++;
                }
            }
        }

        det += (float)(ELMT(m,0,rowMatrix) * (pow(-1,rowMatrix)) * determinant(Co)); // Recursion of Cofactor (if there is any). PS: ngambil kofaktor kolom pertama. perhatikan + - dari kolom pertama aja
    }

    return det;
}
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
Matrix transpose(Matrix m){
    Matrix copy;
    createMatrix(COL_EFF(m), ROW_EFF(m), &copy);
    for (int i = 0; i <= getLastIdxRow(copy); i++){
        for (int j = 0; j <= getLastIdxCol(copy); j++){
            ELMT(copy,j,i) = ELMT(m,i,j);
        }
    }
    return copy;
}
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
void pTranspose(Matrix *m){
    Matrix copy;
    createMatrix(COL_EFF(*m), ROW_EFF(*m), &copy);
    for (int i = 0; i <= getLastIdxRow(copy); i++){
        for (int j = 0; j <= getLastIdxCol(copy); j++){
            ELMT(copy,j,i) = ELMT(*m,i,j);
        }
    }
    *m = copy;
}
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
