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

	printf( "人狼ゲームスタート!\n" );

	do{
		printf( "人数を決めてください。(4～8)\n" );
		scanf( "%d", &Num_people );
	} while ( Num_people < 4 || 8 < Num_people );

	Position jobs[6] = {{"Villager(村人)",0},{"Werewolf(人狼)",1},{"Fortune-teller(占い師)",2},{"Knight(騎士)",3},{"Psyco(狂人)",4},{"Necromancer(霊媒師)",5},{"Lover(恋人)",6}};
	Player info[ Num_people ];

	for( i = 0; i < Num_people; i++ )
	{
		info[i].order = i + 1;

		printf( "Player%dの名前を入力してください。\n", i + 1 );
		scanf( "%s", info[i].name );
	}

	srand( ( unsigned int )time( NULL ) );

		case 4:
		{
			do{
				printf( "\n～役職～\n" );
				printf( "Villager(村人):2\tWerewolf(人狼):1\tFortune-teller(占い師):1\n\n" );
				printf( "確認しましたか。\n" );
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

				printf( "容疑者を処刑したにも関わらず、恐ろしい夜がやってきました。\n" );

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
				printf( "～役職～\n" );
				printf( "村人:1\t人狼:1\t占い師:1\t騎士:1\t狂人:1\n" );
				printf( "確認しましたか。\n" );
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
				printf( "\n～役職～\n" );
				printf( "Villager(村人):2\tWerewolf(人狼):2\tFortune-teller(占い師):1\tKnight(騎士):1\n" );
				printf( "確認しましたか。\n" );
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
				printf( "\n～役職～\n" );
				printf( "Villager(村人):3\tWerewolf(人狼):1\tFortune-teller(占い師):1\tKnight(騎士):1\tPsyco:1\n");
				printf( "確認しましたか。\n");
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

				printf( "容疑者を殺害したにも関わらず、恐ろしい夜がやってきました。\n" );

				night( info, Num_people, i, turn );

			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller + count_knight );

			count_villager_side = count_villager + count_fortuneteller + count_knight;
			count_wolf_side = count_wolf_side;

		}

		case 8:
		{
			do
			{
				printf( "\n～役職～\n" );
				printf( "Villager(村人):2\tWerewolf(人狼):2\tFortune-teller(占い師):1\tKnight(騎士):1\tPsyco(狂人):1\tNecromancer(霊媒師):1\n" );
				printf( "確認しましたか。\n");
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

				printf( "容疑者を殺害したにも関わらず、恐ろしい夜がやってきました。\n" );

				night( info, Num_people, i, turn );

			} while ( count_wolf != 0 && count_wolf < count_villager + count_fortuneteller + count_knight + count_necromancer );

			count_villager_side = count_villager + count_fortuneteller + count_knight + count_necromancer;
			count_wolf_side = count_wolf;
			
			/*if( count_wolf == 0 )
			{
				printf( "人狼を殲滅しました。\n" );
				printf( "人間の勝利です。\n" );
			}
			else if( count_wolf == count_villager + count_fortuneteller + count_knight + count_necromancer )
			{
				printf( "村人と人狼が同数となったので人狼の勝利です。\n" );
			}*/
		}
	}

	new_windows();

	if( count_wolf == 0 )
	{
		printf( "人狼がいなくなりました。\n" );
		printf( "人間の勝利です。\n" );

		flag = 0;
	}
	else if( count_wolf >= count_villager_side )
	{
		printf( "人狼が過半数を占めたので人狼の勝利です。\n" );

		flag = 1;
	}

	if( flag == 0 )
	{
		printf( "\n\n\nWinner!!\n\n");

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number != 1 && info[i].number != 4 )
			{
				printf( "%sさん:%s\t",info[i].name, info[i].job );
			}
		}

		printf( "\n\n\nLoser…\n\n" );

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number == 1 || info[i].number == 4 )
			{
				printf( "%sさん:%s\t", info[i].name, info[i].job );
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
				printf( "%sさん:%s\t", info[i].name, info[i].job );
			}
		}

		printf( "\n\n\nLoser…\n\n" );

		for( i = 0; i < Num_people; i++ )
		{
			if( info[i].number != 1 && info[i].number != 4 )
			{
				printf( "%sさん:%s\t", info[i].name, info[i].job );
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

	printf( "%sさんはVillager(村人)です。\n", info[i].name );

	printf( "数秒後に入力してください。\n");

	sleep( 5 );

	do{
		printf( "確認しましたか。\n" );
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

	printf( "%sさんはWerewolf(人狼)です。\n", info[i].name );
	printf( "誰を殺害しますか。\n" );

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
		printf( "%sさんを殺害しますか。\n", info[ kill[ turn ] - 1 ].name );
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

	printf( "%sさんは(Fortune-teller)占い師です。\n", info[i].name );
	printf( "誰を占いますか。\n" );

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
		printf( "%sさんを占いますか。\n", info[ teller - 1 ].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );

	do{
		if( info[ teller - 1 ].number == 1 )
		{
			printf( "%sさんはWerewolf(人狼)です。\n", info[ teller - 1 ].name );
		}
		else if( info[ teller - 1 ].number != 1 )
		{
			printf( "%sさんはVillager(村人)です。\n", info[ teller - 1 ].name );
		}
	
		printf( "確認しましたか。\n" );
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

	printf( "%sさんは騎士です。\n", info[i].name );
	printf( "誰を人狼の襲撃から守りますか。\n" );

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
		printf( "%sさんを襲撃から守りますか。\n", info[ guard - 1 ].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );
		
	} while ( judg != 1 );

	new_windows();
}

void action_psyco( Player info[], int i )
{
	int judg = 2;

	open_file( 4 );

	printf( "%sさんはPsyco(狂人)です。\n", info[i].name );
	printf( "数秒後に入力してください。\n" );

	sleep( 5 );
	
	do
	{
		printf( "確認しましたか。\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );
	} while ( judg != 1 );

	new_windows();
}

void action_necromancer( Player info[], int i )
{
	int judg = 2;

	open_file( 5 );

	printf ( "%sさんはNecromancer(霊媒師)です。\n", info[i].name );

	do{
		if( info[ exection[ turn - 1 ] - 1 ].number == 1 )
		{
			printf( "処刑者%sさんは村人でした。\n", info[ exection[ turn - 1 ] - 1 ] );
		}
		else if( info[ exection[ turn - 1 ] - 1 ].number != 1 )
		{
			printf( "処刑者%sさんは人狼でした。\n", info[ exection[ turn - 1 ] - 1 ] );
		}

		printf( "確認しましたか。\n" );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

	} while ( judg != 1 );

	new_windows();
}

void action_lover( Player info[], int i )
{
	int judg = 2;

	do{
		printf( "%sさんの役職はLover(恋人)です。\n", info[i].name );

		sleep( 5 );

		printf( "確認しましたか。\n" );
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
		printf( "恐ろしい夜が明けました。\n" );

		if( guard == kill[ turn - 1 ] )
		{
			printf( "昨夜の死亡者はいませんでした。\n" );
		}
		else if( guard != kill[ turn - 1 ] )
		{
			printf( "昨夜の犠牲者は%sさんでした。\n", info[ kill[ turn - 1 ] - 1 ].name );
		}
	}

	printf( "昼の会議を始めてください。\n");
	printf( "制限時間は3分です。\n" );

	sleep( 180 );

	printf( "3分経過しました。\n" );


		do{
			printf( "投票の結果、処刑する人を選択してください。\n" );

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

		printf( "%sさんを処刑しますか。\n", info[ exection[ turn ] - 1 ].name );
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

	printf( "夜の行動を開始します。\n" );

	for( i = 0; i < Num_people; i++ )
	{
		for( j = 0; j < turn + 1; j++ )
		{
			if( info[i].order != exection[j] )
			{
				printf( "%sさんの夜の行動を始めます。\n", info[i].name );

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
		
		printf( "%sさんの役職はVillager(村人)です。\n", info[i].name );

		printf( "あなたは人間です。\n" );
		printf( "人狼を村から追い出しましょう。\n" );

		do{
			printf( "確認しましたか。\n");
			printf( "1:yes    2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );

	}
	else if( info[i].number == 1 )
	{
		int j;

		open_file( 1 );
		
		printf( "%sさんの役職はWerewolf(人狼)です。\n", info[i].name );

		printf( "仲間の人狼は" );

		if( count_wolf == 1 )
		{
			printf( "いません。" );
		}
		else if( count_wolf > 1 )
		{
			for(  j= 0; j < Num_people; j++ )
			{
				if( info[j].number == 1 )
				{
					if( info[i].order != info[j].order )
					{
						printf( "%sさんです。", info[j].name );
					}
				}
			}
		}

		printf( "\n" );
		
		do{
			printf( "確認しましたか。\n");
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
	}
	else if( info[i].number == 2 )
	{
		open_file( 2 );
		
		printf( "%sさんの役職はFortune-teller(占い師)です。\n", info[i].name );

		while( r == i )
		{
			srand( ( unsigned int )time( NULL ) );
			r = rand() % Num_people;
		}
		
		printf( "～～お告げ～～\n" );
		if( info[r].number == 1 )
		{
			printf( "%sさんはWerewolf(人狼)です。\n", info[r].name );
		}
		else if( info[r].number != 1 )
		{
			printf( "%sさんはVillager(村人)です。\n", info[r].name );
		}

		do{
			printf( "確認しましたか。\n");
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );

	}
	else if( info[i].number == 3 )
	{
		open_file( 3 );
		
		printf( "%sさんの役職はKnight(騎士)です。\n",info[i].name );

		printf( "あなたは人間です。\n" );
		printf( "人狼を村から追い出しましょう。\n" );

		do
		{
			printf( "確認しましたか。\n" );
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
			
	}
	else if( info[i].number == 4 )
	{
		open_file( 4 );
		
		printf( "%sさんの役職はPsyco(狂人)です。\n", info[i].name );

		printf( "人狼を勝利に導きましょう。\n" );

		do
		{
			printf( "確認しましたか。\n");
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
	}
	else if( info[i].number == 5 )
	{
		open_file( 5 );

		printf( "%sさんの役職はNecromancer(霊媒師)です。\n", info[i].name );
		printf( "あなたは人間です。\n" );
		printf( "人狼を村から追い出しましょう。\n" );

		do
		{
			printf( "確認しましたか。\n" );
			printf( "1:yes\t2:no\n" );
			scanf( "%d", &judg );
		} while ( judg != 1 );
	}
	else if( info[i].number == 6 )
	{
		int j;

		printf( "%sさんの役職はLover(恋人)です。\n", info[i].name );
			
		for( j = 0; j < Num_people; j++)
		{
			if( info[j].number == 6 )
			{
				if( info[i].order != info[j].order )
				{
					printf( "\nあなたの恋人は%sです。\n", info[j].name );
				}
			}
		}
			
		printf( "あなたは人間です。\n" );
		printf( "人狼を村から追い出しましょう。\n" );
		
		do{
			printf( "確認しましたか。\n" );
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
			strcpy( info[i].job, "Villager(村人)" );
		}
		else if( info[i].number == 1 )
		{
			strcpy( info[i].job, "Werewolf(人狼)" );
		}
		else if( info[i].number == 2 )
		{
			strcpy( info[i].job, "Fortune-teller(占い師)" );
		}
		else if( info[i].number == 3 )
		{
			strcpy ( info[i].job, "Knight(騎士)" );
		}
		else if( info[i].number == 4 )
		{
			strcpy( info[i].job, "Psyco(狂人)" );
		}
		else if( info[i].number == 5 )
		{
			strcpy( info[i].job, "Necromancer(霊媒師)" );
		}
		else if( info[i].number == 6 )
		{
			strcpy( info[i].job, "Lover(恋人)" );
		}
	}
}

void check_people( Player info[], int i )
{
	int judg;

	while( 1 )
	{
		printf( "%sさんの役職を確認します。\n", info[i].name );
		printf( "あなたは%sさんですか。\n", info[i].name );
		printf( "1:yes\t2:no\n" );
		scanf( "%d", &judg );

		if( judg == 1 )
		{
			break;
		}
		else
		{
			printf( "再確認します。\n" );
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