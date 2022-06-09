#include<stdio.h>
#include<stdlib.h>
//コンソル待ちを可能にする
#include<conio.h>
#include<time.h>
#include<string.h>

#define SPELL_COAT (3)


//列挙を分かりやすい索引として使っている
enum CHRACTER
{
	CHARACTER_PLAYER,
	CHARACTER_MONSTER,
	CHARACTER_BOSS,
	CHARACTER_MAX
};
enum MONSTER
{
	MONSTER_PLAYER,
	MONSTER_SLIME,
	MONSTER_BOSS,
	MONSTER_MAX
};
enum COMMAND
{
	COMMAND_FIGHT,
	COMMAND_SPELL,
	COMMAND_RUN,
	COMMAND_MAX
};

typedef struct
{
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	int attack;
	char name[4 * 2 + 1]; //(4char)*(2bite font)+(lastcode)
	char aa[256];
	int command;
	int target;

}CHARACTER;

//使用するものをあらかじめ定義
CHARACTER monsters[MONSTER_MAX] =
{
	//Player
	{
	100,100,25,15,3,"ゆうしゃ",
	},
	//Slime
	{
		3,3,0,0,3,"スライム",
		"`(+o+)'\n"
		"~~~~~~~"
	},
	{
		255,255,0,0,50,"まおう",
		"  A@A\n"
		"$(^m^)$"
	},
};


//実際に表示するものをcharactersに格納する５
CHARACTER characters[CHARACTER_MAX];

char commandNames[COMMAND_MAX][4 * 2 + 1] = {
"たたかう",
"じゅもん",
"にげる"
};

void Init()
{
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

void DrawBattleScreen()
{
	system("cls");

	//プレイヤーのステータスを表示
	printf("%s\n", characters[CHARACTER_PLAYER].name);
	printf("HP:%d/%d MP:%d/%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp
	);

	//モンスターを表示する
	printf("%s", characters[CHARACTER_MONSTER].aa);
	printf("(HP:%d/%d)\n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp);

	printf("\n");

	printf("%sが　現れた\n", characters[CHARACTER_MONSTER].name);
}

void SellectCommand()
{
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;

	while (1)
	{
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			if (i == characters[CHARACTER_PLAYER].command)
			{
				printf(">");
			}
			else
			{
				printf(" ");
			}
			printf(" % s\n", commandNames[i]);
		}

		switch (_getch())
		{
		case 'w':
			characters[CHARACTER_PLAYER].command--;
			break;
		case 's':
			characters[CHARACTER_PLAYER].command++;
			break;

		default:
			return;
		}
		//characters[CHARACTER_PLAYER].command = (COMMAND_MAX+characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
		DrawBattleScreen();
	}
}

void Battle(int _monster)
{
	characters[CHARACTER_MONSTER] = monsters[MONSTER_BOSS];

	//基本的に戦闘が起きるたびに描画処理を発火させる
	DrawBattleScreen();

	_getch();

	//攻撃対象を設定する
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	//戦闘が終わるまでバトルフェイズは続行
	while (1)
	{
		SellectCommand();

		//キャラクとモンスターを走査する
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			DrawBattleScreen();

			switch (characters[i].command)
			{
			case COMMAND_FIGHT:
			{
				printf("%sの　こうげき！", characters[i].name);
				_getch();

				int damage = 1 + rand() % characters[i].attack;
				//敵のダメージを減らす
				characters[characters[i].target].hp -= damage;

				if (characters[characters[i].target].hp < 0)
				{
					characters[characters[i].target].hp = 0;
				}
				DrawBattleScreen();

				printf("%sに　%dのダメージ!\n", characters[characters[i].target].name, damage);
				_getch();

				if (characters[characters[i].target].hp <= 0)
				{
					switch (characters[i].target)
					{
					case CHARACTER_PLAYER:
						printf("あなたは倒されてしまった。。。");
						break;

					case CHARACTER_MONSTER:

						strcpy_s(characters[characters[i].target].aa, "\n");
						DrawBattleScreen();

						printf("%s	を倒した", characters[characters[i].target].name);

						break;
					}

					return;
				}

				_getch();

				break;
			}

			case COMMAND_SPELL: {

				if (characters[i].mp<SPELL_COAT) {
					printf("MPが足りないので呪文が発動できません");
					_getch();
					return;
				}

				printf("%sは　回復呪文を使った！", characters[i].name);
				_getch();

				int hile = 1 + rand() % characters[i].maxHp;
				characters[i].mp -= SPELL_COAT;

				DrawBattleScreen();

				characters[i].hp += hile;

				DrawBattleScreen();

				printf("%s　の傷が回復した");
				_getch();

				break; 
			}

			case COMMAND_RUN:
				printf("%sは　逃げた。。\n", characters[i].name);
				_getch();
				return;
				break;
			}
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	Init();
	Battle(MONSTER_BOSS);
}