#include "InputControl.h"
#include "DxLib.h"

/*****************************
*マクロ定義
* ***************************/
#define XINPUT_BUTTON_MAX (16)         //コントローラーのボタン数

/*****************************
*型定義
* ***************************/
enum KEY_STATE
{
	E_NONE,              //未入力
	E_CLICK,             //押した瞬間
	E_PRESS,             //押し続けてる
	E_RELEASED,          //離した
	E_KEY_STATE_MAX      
};

/*****************************
*変数宣言
* ***************************/
KEY_STATE button_state[XINPUT_BUTTON_MAX];    //各ボタン入力状態

/*****************************
*プロトタイプ宣言
* ***************************/

/*****************************
*入力制御機能:初期化処理
* 引　数:なし
* 戻り値:なし
* ***************************/
void InputControl_Initialize(void)
{
	int i;     //ループカウンタ

	//入力状態の初期化
	for (i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		button_state[i] = E_NONE;
	}

}

/*****************************
* 2
*入力制御機能:更新処理
* 引　数:なし
* 戻り値:なし
* ***************************/
void InputControl_Update(void)
{
	int i;                                 //ループカウンタ
	XINPUT_STATE input_controller;         //コントローラー入力情報

	//コントローラーの入力情報を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input_controller);

	//入力状態の更新
	for (i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		if (input_controller.Buttons[i] == TRUE)
		{
			switch (button_state[i])
			{
			     case E_NONE:
			     case E_RELEASED:
					 button_state[i] = E_CLICK;
					 break;
				 case E_CLICK:
				 case E_PRESS:
					 button_state[i] = E_PRESS;
					 break;
				 default:
					 button_state[i] = E_NONE;
					 break;
			}
		}
		else
		{
			switch (button_state[i])
			{
			     case E_NONE:
				 case E_RELEASED:
					 button_state[i] = E_NONE;
					 break;
				 case E_CLICK:
				 case E_PRESS:
					 button_state[i] = E_RELEASED;
					 break;
				 default:
					 button_state[i] = E_NONE;
					 break;
					 //3
			}
		}
	}
}


