#include<stdio.h>
#include<stdlib.h>
//�R���\���҂����\�ɂ���
#include<conio.h>
#include<time.h>
#include<string.h>

//�񋓂𕪂���₷�������Ƃ��Ďg���Ă���
enum CHRACTER
{
	CHARACTER_PLAYER,
	CHARACTER_MONSTER,
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

//�g�p������̂����炩���ߒ�`
CHARACTER monsters[MONSTER_MAX] =
{
	//Player
	{
	15,15,15,15,3,"�䂤����",
	},
	//Slime
	{
		3,3,0,0,3,"�X���C��",
		"`(+o+)'\n"
		"~~~~~~~"
	},
	{
		255,255,0,0,50,"�܂���",
		" A@A\n"
		"$(^m^)$"
	},
};


//���ۂɕ\��������̂�characters�Ɋi�[����
CHARACTER characters[CHARACTER_MAX];

char commandNames[COMMAND_MAX][4 * 2 + 1] = {
"��������",
"�������",
"�ɂ���"
};

void Init()
{
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

void DrawBattleScreen()
{
	system("cls");

	//�v���C���[�̃X�e�[�^�X��\��
	printf("%s\n", characters[CHARACTER_PLAYER].name);
	printf("HP:%d/%d MP:%d/%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp
	);

	//�����X�^�[��\������
	printf("%s", characters[CHARACTER_MONSTER].aa);
	printf("(HP:%d/%d)\n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp);

	printf("\n");

	printf("%s���@���ꂽ\n", characters[CHARACTER_MONSTER].name);
}

void SellectCommand()
{
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
	characters[CHARACTER_MONSTER] = monsters[MONSTER_SLIME];

	//��{�I�ɐ퓬���N���邽�тɕ`�揈���𔭉΂�����
	DrawBattleScreen();

	_getch();

	//�U���Ώۂ�ݒ肷��
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	//�퓬���I���܂Ńo�g���t�F�C�Y�͑��s
	while (1)
	{
		SellectCommand();

		//�L�����N�ƃ����X�^�[�𑖍�����
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			DrawBattleScreen();

			switch (characters[i].command)
			{
			case COMMAND_FIGHT:
			{
				printf("%s�́@���������I", characters[i].name);
				_getch();

				int damage = 1 + rand() % characters[i].attack;
				//�G�̃_���[�W�����炷
				characters[characters[i].target].hp -= damage;

				if (characters[characters[i].target].hp < 0)
				{
					characters[characters[i].target].hp = 0;
				}
				DrawBattleScreen();

				printf("%s�Ɂ@%d�̃_���[�W!\n", characters[characters[i].target].name, damage);
				_getch();

				if (characters[characters[i].target].hp <= 0)
				{
					switch (characters[i].target)
					{
					case CHARACTER_PLAYER:
						printf("%s	�͓|����Ă��܂���", characters[characters[i].target].name);
						break;

					case CHARACTER_MONSTER:

						strcpy_s(characters[characters[i].target].aa, "\n");
						DrawBattleScreen();

						printf("%s	��|����", characters[characters[i].target].name);

						break;
					}

					return;
				}

				_getch();

				break;
			}

			case COMMAND_SPELL: {
				printf("%s�́@�����I", characters[i].name);
				_getch();

				int damage = 1 + rand() % characters[i].attack;
				//�G�̃_���[�W�����炷
				characters[characters[i].target].hp -= damage;

				if (characters[characters[i].target].hp < 0)
				{
					characters[characters[i].target].hp = 0;
				}
				DrawBattleScreen();

				printf("%s�Ɂ@%d�̃_���[�W!\n", characters[characters[i].target].name, damage);
				_getch();

				if (characters[characters[i].target].hp <= 0)
				{
					switch (characters[i].target)
					{
					case CHARACTER_PLAYER:
						printf("%s	�͓|����Ă��܂���", characters[characters[i].target].name);
						break;

					case CHARACTER_MONSTER:

						strcpy_s(characters[characters[i].target].aa, "\n");
						DrawBattleScreen();

						printf("%s	��|����", characters[characters[i].target].name);

						break;
					}
					return;
				}
				_getch();
				break; 
			}

			case COMMAND_RUN:
				printf("%s�́@�������B�B", characters[i].name);
				_getch();
				return;
			}
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	Init();
	Battle(MONSTER_SLIME);
}