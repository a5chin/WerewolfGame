#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
	char name[31];
	int number;
} Position;

typedef struct
{
	char name[31];
	int number;
	char job[31];
	int order;
} Player;

int count_villager, count_wolf, count_fortuneteller, count_knight, count_psyco, count_necromancer, count_lover, teller;
int count_villager_side = 0, count_wolf_side = 0;
int Num_people = 0, turn = 0, guard = -2;
int exection[100], kill[100];

void action_villager( Player info[], int i );
void action_werewolf( Player info[], int Num_people, int turn, int i );
void action_fortuneteller( Player info[], int Num_people,int i, int turn );
void action_knight( Player info[], int i );
void action_psyco( Player info[], int i );
void action_necromancer( Player info[], int i );
void action_lover( Player info[], int i );
void noon( Player info[], Position jobs[], int turn );
void night( Player info[], int Num_people, int i, int turn );
void count_character( Player info[] );
void copy_charname( Player info[] );
void check_job( Player info[], int Num_people, int i );
void check_people( Player info[], int i );
void distingish( Player info[], int turn, int kill[], int guard );
void new_windows();
void open_file( int kind );

int main( void )
{
	int i, flag;
	int judg = 2;

	exection[0] = -1;
	kill[0] = -1;

	printf( "�l�T�Q�[���X�^�[�g!\n" );

	do{
		printf( "�l�������߂Ă��������B(4�`8)\n" );
		scanf( "%d", &Num_people );
	} while ( Num_people < 4 || 8 < Num_people );

	Position jobs[6] = {{"Villager(���l)",0},{"Werewolf(�l�T)",1},{"Fortune-teller(�肢�t)",2},{"Knight(�R�m)",3},{"Psyco(���l)",4},{"Necromancer(��}�t)",5},{"Lover(���l)",6}};
	Player info[ Num_people ];

	for( i = 0; i < Num_people; i++ )
	{
		info[i].order = i + 1;

		printf( "Player%d�̖��O����͂��Ă��������B\n", i + 1 );
		scanf( "%s", info[i].name );
	}

	srand( ( unsigned int )time( NULL ) );

		case 4:
		{
			do{
				printf( "\n�`��E�`\n" );
				printf( "Villager(���l):2\tWerewolf(�l�T):1\tFortune-teller(�肢�t):1\n\n" );
				printf( "�m�F���܂������B\n" );
				printf( "1:yes\t2:no\n" );
				scanf( "%d", &judg );
			} while ( judg != 1 );

			do{

				count_character( info );

			} while ( count_villager != 2 || count_wolf != 1 || count_fortuneteller != 1 );

			copy_charname( info );

			for( i = 0; i < Num_people; i++ )
			{
				new_windows();

				check_people( info, i );

				check_job( info, Num_people, i );
			}

			new_windows();

			do
			{
				noon( info, jobs, turn );
				
				if( count_wolf == 0 || count_wolf == count_villager + count_fortuneteller )
				{
					break;
				}

				printf( "�e�^�҂����Y�����ɂ��ւ�炸�A���낵���邪����Ă��܂����B\n" );

				night( info, Num_people, i, turn );

				turn++;
		
			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller );

			count_villager_side = count_villager + count_fortuneteller;
			count_wolf_side = count_wolf;

			break;
		}
		
		case 5:
		{
			do
			{
				printf( "�`��E�`\n" );
				printf( "���l:1\t�l�T:1\t�肢�t:1\t�R�m:1\t���l:1\n" );
				printf( "�m�F���܂������B\n" );
				printf( "1:yes\t2:no\n" );
				scanf( "%d", &judg );
			} while ( judg != 1 );

			do
			{
				count_character( info );

			} while ( count_villager != 1 || count_wolf != 1 || count_fortuneteller != 1 || count_knight != 1 || count_psyco != 1 );
			
			copy_charname( info );
			
			for( i = 0; i < Num_people; i++ )
			{
				new_windows();

				check_people( info, i );

				check_job( info, Num_people, i );
			}

			new_windows();

			do
			{
				noon( info, jobs, turn );

				if( count_wolf == 0 || count_wolf >= count_villager + count_fortuneteller + count_knight + count_psyco )
				{
					break;
				}

				night( info, Num_people, i, turn );

				turn++;
				
			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller + count_knight );
			
			count_villager_side = count_villager + count_fortuneteller + count_knight;
			count_wolf_side = count_wolf;

			break;
		}
	
		case 6:
		{
			do
			{
				printf( "\n�`��E�`\n" );
				printf( "Villager(���l):2\tWerewolf(�l�T):2\tFortune-teller(�肢�t):1\tKnight(�R�m):1\n" );
				printf( "�m�F���܂������B\n" );
				printf( "1:yes\t2:no\n" );
				scanf( "%d", &judg );
			} while ( judg != 1 );

			do
			{
				count_character( info );

			} while ( count_villager != 2 || count_wolf != 2 || count_fortuneteller != 1 || count_knight != 1  );

			copy_charname( info );

			for( i = 0; i < Num_people; i++ )
			{
				new_windows();

				check_people( info, i );

				check_job( info, Num_people, i );
			}

			new_windows();

			do
			{
				noon( info, jobs, turn );

				if( count_wolf == 0 || count_wolf == count_villager + count_fortuneteller + count_knight )
				{
					break;
				}

				night( info, Num_people, i, turn );

				turn++;
				
			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller + count_knight );

			count_villager_side = count_villager + count_fortuneteller + count_knight;
			count_wolf_side = count_wolf;

			break;
		}

		case 7:
		{
			do
			{
				printf( "\n�`��E�`\n" );
				printf( "Villager(���l):3\tWerewolf(�l�T):1\tFortune-teller(�肢�t):1\tKnight(�R�m):1\tPsyco:1\n");
				printf( "�m�F���܂������B\n");
				printf( "1:yes\t2:no\n" );
				scanf( "%d", &judg );
			} while ( judg != 1 );

			do
			{
				count_character( info );

			} while ( count_villager != 3 || count_wolf != 1 || count_fortuneteller != 1 || count_knight != 1 || count_psyco != 1 );

			copy_charname( info );

			for( i = 0; i < Num_people; i++ )
			{
				new_windows();

				check_people( info, i );

				check_job( info, Num_people, i );
			}

			new_windows();

			do
			{
				noon( info, jobs, turn );

				if ( count_wolf == 0 || count_wolf == count_villager + count_fortuneteller + count_fortuneteller + count_knight)
				{
					break;
				}

				printf( "�e�^�҂��E�Q�����ɂ��ւ�炸�A���낵���邪����Ă��܂����B\n" );

				night( info, Num_people, i, turn );

			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller + count_knight );

			count_villager_side = count_villager + count_fortuneteller + count_knight;
			count_wolf_side = count_wolf_side;

		}

		case 8:
		{
			do
			{
				printf( "\n�`��E�`\n" );
				printf( "Villager(���l):2\tWerewolf(�l�T):2\tFortune-teller(�肢�t):1\tKnight(�R�m):1\tPsyco(���l):1\tNecromancer(��}�t):1\n" );
				printf( "�m�F���܂������B\n");
				printf( "1:yes\t2:no\n" );
				scanf( "%d", &judg );
			} while ( judg != 1 );

			do
			{
				count_character( info );

			} while ( count_villager != 2 || count_wolf != 2 || count_fortuneteller != 1 || count_psyco != 1 || count_knight != 1 || count_necromancer != 1 );

			copy_charname( info );

			for( i = 0; i < Num_people; i++ )
			{
				new_windows();

				check_people( info, i );

				check_job( info, Num_people, i );
			}

			new_windows();

			do
			{
				noon( info, jobs, turn );

				if ( count_wolf == 0 || count_wolf == count_villager + count_fortuneteller + count_fortuneteller + count_knight + count_necromancer )
				{
					break;
				}

				printf( "�e�^�҂��E�Q�����ɂ��ւ�炸�A���낵���邪����Ă��܂����B\n" );

				night( info, Num_people, i, turn );

			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller + count_knight + count_necromancer );

			count_villager_side = count_villager + count_fortuneteller + count_knight + count_necromancer;
			count_wolf_side = count_wolf;
			
			/*if( count_wolf == 0 )
			{
				printf( "�l�T��r�ł��܂����B\n" );
				printf( "�l�Ԃ̏����ł��B\n" );
			}
			else if( count_wolf == count_villager + count_fortuneteller + count_knight + count_necromancer )
			{
				printf( "���l�Ɛl�T�������ƂȂ����̂Ől�T�̏����ł��B\n" );
			}*/
		}
	}

	new_windows();

	if( count_wolf == 0 )
	{
		printf( "�l�T�����Ȃ��Ȃ�܂����B\n" );
		printf( "�l�Ԃ̏����ł��B\n" );

		flag = 0;
	}
	else if( count_wolf >= count_villager_side )
	{
		printf( "�l�T���ߔ������߂��̂Ől�T�̏����ł��B\n" );

		flag = 1;
	}

	if( flag == 0 )
	{
		printf( "\n\n\nWinner!!\n\n");

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number != 1 && info[i].number != 4 )
			{
				printf( "%s����:%s\t",info[i].name, info[i].job );
			}
		}

		printf( "\n\n\nLoser�c\n\n" );

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number == 1 || info[i].number == 4 )
			{
				printf( "%s����:%s\t", info[i].name, info[i].job );
			}
		}

	}
	else if( flag == 1 )
	{
		printf( "\n\n\nWinner!!\n\n" );

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number == 1 || info[i].number == 4 )
			{
				printf( "%s����:%s\t", info[i].name, info[i].job );
			}
		}

		printf( "\n\n\nLoser�c\n\n" );

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number != 1 && info[i].number != 4 )
			{
				printf( "%s����:%s\t", info[i].name, info[i].job );
			}
		}
	}
	
	printf( "\n\n" );

	return 0;
}

void action_villager(  Player info[], int i )
{
	int judg = 2;

	open_file( 0 );

	printf( "%s�����Villager(���l)�ł��B\n", info[i].name );

	printf( "���b��ɓ��͂��Ă��������B\n");

	sleep( 5 );

	do{
		printf( "�m�F���܂������B\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );
	} while ( judg == 2 );

	new_windows();
}

void action_werewolf( Player info[], int Num_people, int i, int turn )
{
	int j, k;
	int judg = 2;

	open_file( 1 );

	printf( "%s�����Werewolf(�l�T)�ł��B\n", info[i].name );
	printf( "�N���E�Q���܂����B\n" );

	do{
		for( j = 0; j < Num_people; j++ )
		{
			for( k = 0; k < turn + 1; k++ )
			{
				if( info[j].order != exection[k] )
				{
					if( turn != 0 )
					{
						if( info[j].order != kill[ turn - 1 ] )
						{
							if( info[j].number != 1)
							{
								printf( "%d:%s\t", j + 1, info[j].name );
							}
						}
					}
					else if( turn == 0 )
					{
						if( info[j].number != 1 )
						{
							printf( "%d:%s\t", j + 1, info[j].name );
						}
					}
				}
			}
		}

		printf( "\n" );
		scanf( "%d", &kill[ turn ] );
		printf( "%s������E�Q���܂����B\n", info[ kill[ turn ] - 1 ].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );
	
	new_windows();
}

void action_fortuneteller(  Player info[], int Num_people, int i, int turn )
{
	int j, k;
	int judg = 2;

	open_file( 2 );

	printf( "%s�����(Fortune-teller)�肢�t�ł��B\n", info[i].name );
	printf( "�N��肢�܂����B\n" );

	do
	{
		for( j = 0; j < Num_people; j++ )
		{
			for( k = 0; k < turn + 1; k++ )
			{
				if( info[j].order != exection[k] )
				{
					if( turn != 0 )
					{
						if( info[j].number != kill[ turn - 1 ] )
						{
							if( info[j].number != 2 )
							{
								printf( "%d:%s\t", j + 1, info[j].name );
							}
						}
					}
					else if( turn == 0)
					{
						if( info[j].number != 2 )
						{
							printf( "%d:%s\t", j + 1, info[j].name );
						}
					}
				}
			}
		}

		printf( "\n" );
		scanf( "%d", &teller );
		printf( "%s�����肢�܂����B\n", info[ teller - 1 ].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );

	do{
		if( info[ teller - 1 ].number == 1 )
		{
			printf( "%s�����Werewolf(�l�T)�ł��B\n", info[ teller - 1 ].name );
		}
		else if( info[ teller - 1 ].number != 1 )
		{
			printf( "%s�����Villager(���l)�ł��B\n", info[ teller - 1 ].name );
		}
	
		printf( "�m�F���܂������B\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );
	
	new_windows();
}

void action_knight( Player info[], int i )
{
	int  j, k;
	int judg = 2;

	open_file( 3 );

	printf( "%s����͋R�m�ł��B\n", info[i].name );
	printf( "�N��l�T�̏P��������܂����B\n" );

	do
	{
		for( j = 0; j < Num_people; j++ )
		{
			for( k = 0; k < turn + 1; k++ )
			{
				if( info[j].order != exection[k] )
				{
					if( turn != 0 )
					{
						if( info[j].number != kill[ turn - 1 ] )
						{
							if( info[j].number != 3 )
							{
								printf( "%d:%s\t", j + 1, info[j].name );
							}
						}
					}
					else if( turn == 0)
					{
						if( info[j].number != 3 )
						{
							printf( "%d:%s\t", j + 1, info[j].name );
						}
					}
				}
			}
		}
		
		printf( "\n" );
		scanf( "%d", &guard );
		printf( "%s������P��������܂����B\n", info[ guard - 1 ].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );
		
	} while ( judg != 1 );

	new_windows();
}

void action_psyco( Player info[], int i )
{
	int judg = 2;

	open_file( 4 );

	printf( "%s�����Psyco(���l)�ł��B\n", info[i].name );
	printf( "���b��ɓ��͂��Ă��������B\n" );

	sleep( 5 );
	
	do
	{
		printf( "�m�F���܂������B\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );
	} while ( judg != 1 );

	new_windows();
}

void action_necromancer( Player info[], int i )
{
	int judg = 2;

	open_file( 5 );

	printf ( "%s�����Necromancer(��}�t)�ł��B\n", info[i].name );

	do{
		if( info[ exection[ turn - 1 ] - 1 ].number == 1 )
		{
			printf( "���Y��%s����͑��l�ł����B\n", info[ exection[ turn - 1 ] - 1 ] );
		}
		else if( info[ exection[ turn - 1 ] - 1 ].number != 1 )
		{
			printf( "���Y��%s����͐l�T�ł����B\n", info[ exection[ turn - 1 ] - 1 ] );
		}

		printf( "�m�F���܂������B\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );

	new_windows();
}

void action_lover( Player info[], int i )
{
	int judg = 2;

	do{
		printf( "%s����̖�E��Lover(���l)�ł��B\n", info[i].name );

		sleep( 5 );

		printf( "�m�F���܂������B\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );
}

void noon( Player info[], Position jobs[], int turn )
{
	int i, j;
	int judg = 2;
	
	if( turn > 0 )
	{
		printf( "���낵���邪�����܂����B\n" );

		if( guard == kill[ turn - 1 ] )
		{
			printf( "���̎��S�҂͂��܂���ł����B\n" );
		}
		else if( guard != kill[ turn - 1 ] )
		{
			printf( "���̋]���҂�%s����ł����B\n", info[ kill[ turn - 1 ] - 1 ].name );
		}
	}

	printf( "���̉�c���n�߂Ă��������B\n");
	printf( "�������Ԃ�3���ł��B\n" );

	sleep( 180 );

	printf( "3���o�߂��܂����B\n" );


		do{
			printf( "���[�̌��ʁA���Y����l��I�����Ă��������B\n" );

			if( turn > 0 )
			{
				for( i = 0; i < Num_people; i++ )
				{
					for( j = 0; j < turn; j++ )
					{
						if( guard != kill[ turn - 1 ] )
						{
							if( ( i + 1 ) != kill[ turn - 1 ] )
							{
								if( ( i + 1 ) != exection[j] )
								{
									printf( "%d:%s\t", i + 1, info[i].name );
								}
							}
						}
					}
				}
			}
			else if( turn == 0 )
			{
				for( i = 0; i < Num_people; i++ )
				{
					printf( "%d:%s\t", i + 1, info[i].name );
				}
				
			}

		printf( "\n" );

		scanf( "%d", &exection[ turn ] );

		printf( "%s��������Y���܂����B\n", info[ exection[ turn ] - 1 ].name );
		printf( "1:yes    2:no\n" );
		scanf( "%d", &judg );

		if( judg == 1 )
		{
			break;
		}
		else if( judg != 1 )
		{
			exection[ turn ] = -1;
		}

	} while ( judg != 1 );

	if( info[ exection[ turn ] - 1 ].number == 0 )
	{
		count_villager--;
	}
	else if( info[ exection[ turn ] - 1 ].number == 1 )
	{
		count_wolf--;
	}
	else if ( info[ exection[ turn ] - 1 ].number == 2 )
	{
		count_fortuneteller--;
	}
	else if( info [ exection[ turn ] - 1 ].number == 3 )
	{
		count_knight--;
	}
	else if( info[ exection[ turn ] - 1 ].number == 4 )
	{
		count_psyco--;
	}
	else if( info[ exection[ turn ] - 1 ].number == 5 )
	{
		count_necromancer--;
	}
	else if( info[ exection[ turn ] - 1 ].number == 6 )
	{
		count_lover -= 2;
	}
}

void night( Player info[], int Num_people, int i, int turn )
{
	int j;
	int judg = 2;

	printf( "��̍s�����J�n���܂��B\n" );

	for( i = 0; i < Num_people; i++ )
	{
		for( j = 0; j < turn + 1; j++ )
		{
			if( info[i].order != exection[j] )
			{
				printf( "%s����̖�̍s�����n�߂܂��B\n", info[i].name );

				check_people( info, i );

				if( info[i].number == 0 )
				{
					action_villager( info, i );
				}
				else if( info[i].number == 1 )
				{
					action_werewolf( info, Num_people, i, turn );
				}
				else if( info[i].number == 2 )
				{
					action_fortuneteller( info, Num_people, i, turn );
				}
				else if( info[i].number == 3 )
				{
					action_knight( info, i );
				}
				else if( info[i].number == 4 )
				{
					action_psyco( info, i );
				}
				else if( info[i].number == 5 )
				{
					action_necromancer( info, i );
				}
				else if( info[i].number == 6 )
				{
					action_lover(  info, i );
				}
			}
		}
	}

	distingish( info, turn, kill, guard );
}

void check_job( Player info[], int Num_people, int i )
{
	int judg = 2;
	int r = i;

	if( info[i].number == 0 )
	{
		open_file( 0 );
		
		printf( "%s����̖�E��Villager(���l)�ł��B\n", info[i].name );

		printf( "���Ȃ��͐l�Ԃł��B\n" );
		printf( "�l�T�𑺂���ǂ��o���܂��傤�B\n" );

		do{
			printf( "�m�F���܂������B\n");
			printf( "1:yes    2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );

	}
	else if( info[i].number == 1 )
	{
		int j;

		open_file( 1 );
		
		printf( "%s����̖�E��Werewolf(�l�T)�ł��B\n", info[i].name );

		printf( "���Ԃ̐l�T��" );

		if( count_wolf == 1 )
		{
			printf( "���܂���B" );
		}
		else if( count_wolf > 1 )
		{
			for(  j= 0; j < Num_people; j++ )
			{
				if( info[j].number == 1 )
				{
					if( info[i].order != info[j].order )
					{
						printf( "%s����ł��B", info[j].name );
					}
				}
			}
		}

		printf( "\n" );
		
		do{
			printf( "�m�F���܂������B\n");
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
	}
	else if( info[i].number == 2 )
	{
		open_file( 2 );
		
		printf( "%s����̖�E��Fortune-teller(�肢�t)�ł��B\n", info[i].name );

		while( r == i )
		{
			srand( ( unsigned int )time( NULL ) );
			r = rand() % Num_people;
		}
		
		printf( "�`�`�������`�`\n" );
		if( info[r].number == 1 )
		{
			printf( "%s�����Werewolf(�l�T)�ł��B\n", info[r].name );
		}
		else if( info[r].number != 1 )
		{
			printf( "%s�����Villager(���l)�ł��B\n", info[r].name );
		}

		do{
			printf( "�m�F���܂������B\n");
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );

	}
	else if( info[i].number == 3 )
	{
		open_file( 3 );
		
		printf( "%s����̖�E��Knight(�R�m)�ł��B\n",info[i].name );

		printf( "���Ȃ��͐l�Ԃł��B\n" );
		printf( "�l�T�𑺂���ǂ��o���܂��傤�B\n" );

		do
		{
			printf( "�m�F���܂������B\n" );
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
			
	}
	else if( info[i].number == 4 )
	{
		open_file( 4 );
		
		printf( "%s����̖�E��Psyco(���l)�ł��B\n", info[i].name );

		printf( "�l�T�������ɓ����܂��傤�B\n" );

		do
		{
			printf( "�m�F���܂������B\n");
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
	}
	else if( info[i].number == 5 )
	{
		open_file( 5 );

		printf( "%s����̖�E��Necromancer(��}�t)�ł��B\n", info[i].name );
		printf( "���Ȃ��͐l�Ԃł��B\n" );
		printf( "�l�T�𑺂���ǂ��o���܂��傤�B\n" );

		do
		{
			printf( "�m�F���܂������B\n" );
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
	}
	else if( info[i].number == 6 )
	{
		int j;

		printf( "%s����̖�E��Lover(���l)�ł��B\n", info[i].name );
			
		for( j = 0; j < Num_people; j++)
		{
			if( info[j].number == 6 )
			{
				if( info[i].order != info[j].order )
				{
					printf( "\n���Ȃ��̗��l��%s�ł��B\n", info[j].name );
				}
			}
		}
			
		printf( "���Ȃ��͐l�Ԃł��B\n" );
		printf( "�l�T�𑺂���ǂ��o���܂��傤�B\n" );
		
		do{
			printf( "�m�F���܂������B\n" );
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );

			printf( "\n" );
		} while ( judg != 1 );
	}
}

void count_character( Player info[] )
{
	int i;

	count_villager = 0, count_wolf = 0, count_fortuneteller = 0, count_knight = 0, count_psyco = 0, count_necromancer = 0, count_lover = 0;

	for( i = 0; i < Num_people; i++ )
	{
		info[i].number = rand() % Num_people ;

		if( info[i].number == 0 )
		{
			count_villager++;
		}
		else if( info[i].number == 1 )
		{
			count_wolf++;
		}
		else if( info[i].number == 2 )
		{
			count_fortuneteller++;
		}
		else if( info[i].number == 3 )
		{
			count_knight++;
		}
		else if( info[i].number == 4 )
		{
			count_psyco++;
		}
		else if( info[i].number == 5 )
		{
			count_necromancer++;
		}
		else if( info[i].number == 6 )
		{
			count_lover++;
		}
	}
}

void copy_charname( Player info[] )
{
	int i;

	for( i = 0; i < Num_people; i++ )
	{
		if( info[i].number == 0 )
		{
			strcpy( info[i].job, "Villager(���l)" );
		}
		else if( info[i].number == 1 )
		{
			strcpy( info[i].job, "Werewolf(�l�T)" );
		}
		else if( info[i].number == 2 )
		{
			strcpy( info[i].job, "Fortune-teller(�肢�t)" );
		}
		else if( info[i].number == 3 )
		{
			strcpy ( info[i].job, "Knight(�R�m)" );
		}
		else if( info[i].number == 4 )
		{
			strcpy( info[i].job, "Psyco(���l)" );
		}
		else if( info[i].number == 5 )
		{
			strcpy( info[i].job, "Necromancer(��}�t)" );
		}
		else if( info[i].number == 6 )
		{
			strcpy( info[i].job, "Lover(���l)" );
		}
	}
}

void check_people( Player info[], int i )
{
	int judg;

	while( 1 )
	{
		printf( "%s����̖�E���m�F���܂��B\n", info[i].name );
		printf( "���Ȃ���%s����ł����B\n", info[i].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

		if( judg == 1 )
		{
			break;
		}
		else
		{
			printf( "�Ċm�F���܂��B\n" );
		}
	}
}

void distingish( Player info[], int turn, int kill[], int guard )
{

	if( info[ kill[ turn ] - 1 ].number == 0 )
	{
		if( guard != kill[ turn ] )
		{
			count_villager--;
		}
	}
	else if( info[ kill[ turn ] - 1 ].number == 2 )
	{
		if( guard != kill[ turn ] )
		{
			count_fortuneteller--;
		}
	}
	else if( info[ kill[ turn ] - 1 ].number == 3 )
	{
		count_knight--;
	}
	else if( info[ kill[ turn ] - 1 ].number == 4 )
	{
		if( guard != kill[ turn ] )
		{	
			count_psyco--;
		}
	}
	else if( info[ kill[ turn ] - 1 ].number == 5 )
	{
		if( guard != kill[ turn ] )
		{
			count_necromancer--;
		}
	}
	else if( info[ kill[ turn ] - 1 ].number == 6 )
	{
		if( guard != kill[ turn ] )
		{
			count_lover -= 2;
		}
	}
}

void new_windows()
{
	int new_line;

		for( new_line = 0; new_line < 1050; new_line++ )
		{
			printf( "\n" );
		}
}

void open_file( int kind )
{
	FILE* fp;

	char c;

	if( kind == 0 )
	{
		fp = fopen( "villager.txt", "r" );
	}
	else if( kind == 1 )
	{
		fp = fopen( "werewolf.txt", "r" );
	}
	else if( kind == 2 )
	{
		fp = fopen( "fortune-teller.txt", "r");
	}
	else if( kind == 3 )
	{
		fp = fopen( "knight.txt", "r" );
	}
	else if( kind == 4 )
	{
		fp = fopen( "psyco.txt", "r" );
	}
	else if( kind == 5 )
	{
		fp = fopen( "necromancer.txt", "r" );
	}

	while( ( c = fgetc( fp ) ) != EOF )
	{
		printf( "%c", c );
	}

	printf( "\n" );

	fclose( fp );
}