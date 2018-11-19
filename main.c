// Main program untuk tictactoe
// Pandyaka Aptanagi / 13517003

#include <stdio.h>
#include "boolean.h"
#include <string.h>
#include <stdlib.h>

#define StartUser "o---x----"	// Definisi start state user
#define StartComp "----o----"	// Definisi start state komputer 
	
// Deklarasi type bentukan	
	
	typedef struct
		{
			char s[11];
		} kata;
	
	typedef struct
		{
			kata M[150][10];
		} MATRIX;

// Deklarasi fungsi dan prosedur

	boolean IsGiliranValid ( char x);
	// Fungsi untuk check apakah input giliran yang dimasukkan oleh player valid
	
	void TampilkanTTT ( char s[11] );
	// I.S = Sembarang, bisa kotak kosong
	// F.S = Kotak dengan isi 'X' dan atau 'O' sesuai dengan state yang berjalan
	
	MATRIX assignFile(FILE *fp);
	// Fungsi untuk mengassign file eksternal ke dalam matriks
	
	boolean Win(char s[12]);
	// Fungsi untuk mengecek apakah komputer sudah menang atau belum
	
	boolean Draw (char s[12]);
	// Fungsi untuk mengecek apakah seri atau tidak
	
	void Transisi( MATRIX temp , kata state1, int x  , kata *state2);
	// I.S = State awal terdefinisi, MATRIX temp berisi kumpulan state, x terdefinisi sebagai transisi fungsi
	// F.S = State2 berisi state yang memiliki kolom ke-i dari baris state awal 
	
// Program utama

	int main ()
		{
			// Kamus
			char Giliran;
			FILE *fp;
			kata TempSt, State;
			MATRIX MState;
			boolean win,draw;
			int in;
			MATRIX tempstate;
			int count;
			int i;

			
			// Algoritma
				
				// UI Awal
					printf("   ========= Tic Tac Toe =========	\n");
					printf("   									\n");
					printf("|	Welcome to TicTacToe	    | 	\n");
					printf("|	Pandyaka A / 13517003	    | 	\n");
					printf("									\n");
					printf("   ===============================	\n");
					
					printf("Setiap awal permainan, selalu ambil posisi 5\n");
					printf("Player bernilai 'X' , sedangkan CPU bernilai 'O'\n");
					printf("\n");
			
				// UI Awal ditambah dengan pilihan permainan
					printf("Player silahkan pilih P \n");
					printf("CPU silahkan pilih C \n");
					printf("Silahkan pilih siapa yang memulai terlebih dahulu : ");
					scanf("%c",&Giliran);
				
				// Jika input tidak valid, akan looping sampai input valid
					
					while ( !IsGiliranValid(Giliran) )
						{
							printf("Maaf, masukan anda tidak valid!\n");
							printf("Silahkan masukkan kembali giliran yang anda pilih : \n");
							scanf("%c",&Giliran);
						};
					
				// Jika input valid, akan masuk ke start state
					
					// Membuka file eksternal
						if ( Giliran == 'C' || Giliran == 'c' )
							{
								fp = fopen("computer.txt","r"); // Membuka file computer first
								strcpy(TempSt.s,StartComp); // Menampung posisi awal comp di temp state
							}
						else 
							{
								fp = fopen("user.txt","r"); // Membuka file user first
								strcpy(TempSt.s,StartUser); // Menampung posisi awal user di temp state
							};
					
					// Menampilkan start state sebagai state awal
						TampilkanTTT(TempSt.s);
						
					// Assign file eksternal
						MState = assignFile(fp);
					
					// Program Utama 
						win = false;	
						draw = false;	
						count = 0;
						
						while ( ( !win ) && ( !draw ) )
							{
								printf("\n");
								printf("Silahkan, giliran Anda : ");
								scanf("%d",&in);
									
								while ( (in < 1) || ( in > 9)	)
									{
										printf("Masukan Anda salah\n");
										printf("Silahkan masukkan kembali : ");
										scanf("%d",&in);
									};
									
								Transisi(MState, TempSt, in, &State);

								while ( strcmp(State.s , TempSt.s) == 0 )
									{
										printf("Kotak penuh\n");
										printf("Silahkan isi nomor lain : ");
										scanf("%d",&in);
										
										Transisi(MState, TempSt, in, &State);
									} 
								
								strcpy(tempstate.M[1][count].s , State.s);
								count = count + 1;	
								TempSt = State;
								TampilkanTTT(TempSt.s);
								
								win = Win(TempSt.s);
								draw = Draw(TempSt.s);
							}
						
						if ( win )
							{
								printf("\n");
								printf("Maaf nih Anda kalah.\n");
							}
						else
						if ( draw )
							{
								printf("\n");
								printf("Maaf nih Anda seri.\n");
							};
							
						printf("State yang sudah dilalui :\n");
						i = 0;
						while ( i < count )
							{
								printf("%s ",tempstate.M[1][i].s);
								if ( i != count-1)
									{
										printf(" -> ");	
									}	
								i++;
							}
						printf("%s ",tempstate.M[1][count].s);
		};

// Implementasi fungsi dan prosedur	

	boolean IsGiliranValid ( char x)
		// Fungsi untuk check apakah input giliran yang dimasukkan oleh player valid
		{
			// Kamus
			
			// ALgoritma
			return ( x == 'C' || x == 'c' || x == 'P' || x == 'p');
		};
	
	void TampilkanTTT ( char s[11] )
	// Prosedur untuk menampilkan tampilan permainan tictactoe
		{
			// Kamus
			int i;
			
			// Algoritma
			printf("===============");
			printf("\n");
			printf("|");
			
			for ( i = 0 ; i < 9 ; i++)
				{
					if ( s[i] == 'x')
						{
							printf(" X |");
						}
					else
					if ( s[i] == 'o' )
						{
							printf(" O |");
						}
					else
						{
							printf(" - |");
						}
						if ((i == 2) || (i == 5) || (i == 8))
				        {
				            printf("\n");
				            printf("===============");
				            if (i != 8)
				            {
				                printf("\n");
				                printf("|");
				            }
				        }
				    }
				
		}
		
		
	MATRIX assignFile(FILE *fp)
	// Fungsi untuk mengassign file eksternal ke dalam matriks
		{
			// Kamus
				int i,j;
				MATRIX M;
				
			// Algoritma
			for ( i = 0 ; i <= 135 ; i++) // untuk membaca baris
				{
					for ( j = 0 ; j <= 9 ; j++ ) // untuk baca kolom
						{
							fscanf(fp , "%s", &M.M[i][j].s);
						};
				};
			return M;
		}
		
	boolean Win(char s[12])
	// Fungsi untuk mengecek apakah komputer sudah menang atau belum
		{
			// Kamus
			
			// Algoritma
			return ( s[9] == 'w' ); // Memanfaatkan file eksternal
		}; 
	
	boolean Draw (char s[12])
	// Fungsi untuk mengecek apakah seri atau tidak
		{
			// Kamus
			
			// Algoritma
			return ( s[9] == 'd' ); // Memanfaatkan file eksternal
		};
	
	void Transisi( MATRIX temp , kata state1 , int x  , kata *state2)
	// I.S = State awal terdefinisi, MATRIX temp berisi kumpulan state, x terdefinisi sebagai transisi fungsi
	// F.S = State2 berisi state yang memiliki kolom ke-i dari baris state awal 
		
		{
				// Kamus
			    int i,j;
			    boolean found;
				boolean sama;
				kata state3;
				kata state4;
				
				// Algoritma
			    j = 0;
			    found = false;
				sama = false;
				
			    while ((j < 150) && (!found))
			    {
			        if (strcmp(temp.M[j][0].s,state1.s) == 0)
			        {
			            *state2 = temp.M[j][x];
			            state3 = *state2;
			            found = true;
			        }
			        else
			        j++;
			    }
			    
			    
			    while ( ( i < 150 ) && (!sama) )
			    	{
			    		if ( strcmp(state3.s,temp.M[i][0].s) == 0 )
			    			{
			    				sama = true;
							};
						i++;
					};
					
							printf("State yang dilalui : q%d\n",i);
				 	 		printf("State yang dilalui : %s\n",*state2);

    
		};
