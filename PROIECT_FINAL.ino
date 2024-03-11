#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int currentPlayer = 1;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("X si 0");

  delay(2000);

  lcd.clear();
  DrawBoard();

  lcd.setCursor(0, 1);
  lcd.print("Player 1's turn");

  Serial.println("X si 0");
  DisplayTurn();

}

void loop()
{
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    if (input >= '1' && input <= '9')
    {
      int position = input - '1';
      int row = 2 - position / 3;
      int col = position % 3;

      if (board[row][col] == ' ')
      {
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';
        DrawBoard();

        if (CheckWinner())
        {
          lcd.setCursor(0, 1);
          lcd.print("Player ");
          lcd.print(currentPlayer);
          lcd.print(" wins!");

          Serial.print("Player ");
          Serial.print(currentPlayer);
          Serial.println(" wins!");

          delay(2000);
          ResetGame();
        }
        else if (IsBoardFull())
        {
          lcd.setCursor(0, 1);
          lcd.print("It's a draw!");

          Serial.println("It's a draw!");

          delay(2000);
          ResetGame();
        }
        else
        {
          currentPlayer = 3 - currentPlayer; // Schimbă jucătorul (1 devine 2, 2 devine 1)
          DisplayTurn();
        }
      }
    }
  }
}

void DrawBoard()
{
  lcd.clear();

  for (int row = 0; row < 3; ++row)
  {
    if(row==0){
      lcd.setCursor(0, 0);
    for (int col = 0; col < 3; ++col)
    {
      lcd.write(board[0][col]);
      Serial.print(board[0][col]); // Afișare pe Serial Monitor
      if (col < 2)
      {
        lcd.print("");
        Serial.print(" | ");
      }
    }
    Serial.println();
    }

    lcd.print("|");

    if(row==1){
      lcd.setCursor(4,0);
    for (int col = 0; col < 3; ++col)
    {
      lcd.write(board[1][col]);
      Serial.print(board[1][col]); // Afișare pe Serial Monitor
      if (col < 2)
      {
        lcd.print("");
        Serial.print(" | ");
      }
    }
    Serial.println();
    }

    lcd.print("|");

    if(row==2){
      lcd.setCursor(8,0);
    for (int col = 0; col < 3; ++col)
    {
      lcd.write(board[2][col]);
      Serial.print(board[2][col]); // Afișare pe Serial Monitor
      if (col < 2)
      {
        lcd.print("");
        Serial.print(" | ");
      }
    }
    Serial.println();
    }
  }
}




void DisplayTurn()
{
  lcd.setCursor(0, 1);
  lcd.print("Player ");
  lcd.print(currentPlayer);
  lcd.print("'s turn");

  Serial.print("Player ");
  Serial.print(currentPlayer);
  Serial.println("'s turn");
}

bool CheckWinner()
{
  // verifica liniile
  for (int i = 0; i < 3; ++i)
  {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
      return true;
  }

  // verifica pe coloane
  for (int i = 0; i < 3; ++i)
  {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
      return true;
  }

  // verifica pe diagonale
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    return true;

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
 {
    lcd.setCursor(0, 1);
    lcd.print("Player ");
    lcd.print(currentPlayer);
    lcd.print(" wins!");

    Serial.print("Player ");
    Serial.print(currentPlayer);
    Serial.println(" wins!");

    delay(2000);
    ResetGame();
    return true;
  }

  return false;
}

bool IsBoardFull() //verifica daca jocul s-a terminat
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      if (board[i][j] == ' ')
        return false;
    }
  }
  return true;
}

void ResetGame() // resetam jocul
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      board[i][j] = ' ';
    }
  }
  currentPlayer = 1;
  lcd.clear();
  DrawBoard();
  DisplayTurn();
}
