#include <string.h>
#include "LedControl.h"

#define CHAR_WIDTH 7
#define CHAR_HEIGHT 5
#define MAX_CHARACTERS 255

struct CharMatrix
{
  uint8_t letter_rows[8];
};

CharMatrix char_A = {
  {
    0b01110000,
    0b10001000,
    0b10001000,
    0b11111000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_B = {
  {
    0b11110000,
    0b10001000,
    0b10001000,
    0b11110000,
    0b10001000,
    0b10001000,
    0b11110000,
    0b00000000
  }
};

CharMatrix char_C = {
  {
    0b01110000,
    0b10001000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10001000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_D = {
  {
    0b11110000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b11110000,
    0b00000000
  }
};

CharMatrix char_E = {
  {
    0b11111000,
    0b10000000,
    0b10000000,
    0b11110000,
    0b10000000,
    0b10000000,
    0b11111000,
    0b00000000
  }
};

CharMatrix char_F = {
  {
    0b11111000,
    0b10000000,
    0b10000000,
    0b11110000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000
  }
};

CharMatrix char_G = {
  {
    0b01110000,
    0b10001000,
    0b10000000,
    0b10000000,
    0b10011000,
    0b10001000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_H = {
  {
    0b10001000,
    0b10001000,
    0b10001000,
    0b11111000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_I = {
  {
    0b01110000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_J = {
  {
    0b00111000,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00001000,
    0b01001000,
    0b00110000,
    0b00000000
  }
};

CharMatrix char_K = {
  {
    0b10001000,
    0b10010000,
    0b10100000,
    0b11000000,
    0b10100000,
    0b10010000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_L = {
  {
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b11111000,
    0b00000000
  }
};

CharMatrix char_M = {
  {
    0b10001000,
    0b11011000,
    0b10101000,
    0b10101000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_N = {
  {
    0b10001000,
    0b10001000,
    0b11001000,
    0b10101000,
    0b10011000,
    0b10001000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_O = {
  {
    0b01110000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_P = {
  {
    0b11110000,
    0b10001000,
    0b10001000,
    0b11110000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000
  }
};

CharMatrix char_Q = {
  {
    0b01110000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b01110000,
    0b00001000,
    0b00000000
  }
};

CharMatrix char_R = {
  {
    0b11110000,
    0b10001000,
    0b10001000,
    0b11110000,
    0b10100000,
    0b10010000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_S = {
  {
    0b01110000,
    0b10001000,
    0b10000000,
    0b01110000,
    0b00001000,
    0b10001000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_T = {
  {
    0b11111000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00000000
  }
};

CharMatrix char_U = {
  {
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_V = {
  {
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b01010000,
    0b00100000,
    0b00000000
  }
};

CharMatrix char_W = {
  {
    0b10001000,
    0b10001000,
    0b10001000,
    0b10001000,
    0b10101000,
    0b10101000,
    0b01010000,
    0b00000000
  }
};

CharMatrix char_X = {
  {
    0b10001000,
    0b10001000,
    0b01010000,
    0b00100000,
    0b01010000,
    0b10001000,
    0b10001000,
    0b00000000
  }
};

CharMatrix char_Y = {
  {
    0b10001000,
    0b10001000,
    0b10001000,
    0b01111000,
    0b00001000,
    0b10001000,
    0b01110000,
    0b00000000
  }
};

CharMatrix char_Z = {
  {
    0b11111000,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b11111000,
    0b00000000
  }
};

CharMatrix char_SPACE = {
  {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
  }
};

class TextDisplayer
{
public:
  TextDisplayer(LedControl* matrix, bool is_reverse) : 
    m_matrix(matrix),
    m_is_reverse(is_reverse) 
  {
    m_current_width = is_reverse ? CHAR_WIDTH : 0;
  }

  void apply_text(const char* text, bool add_new_line = true)
  {
    int text_length = strlen(text);

    if (text_length > MAX_CHARACTERS - 1) return;
    if (text_length <= 0) return;

    for (int i = 0; i < text_length; i++)
    {
      if (text[i] == 'a') m_text[i] = char_A;
      if (text[i] == 'b') m_text[i] = char_B;
      if (text[i] == 'c') m_text[i] = char_C;
      if (text[i] == 'd') m_text[i] = char_D;
      if (text[i] == 'e') m_text[i] = char_E;
      if (text[i] == 'f') m_text[i] = char_F;
      if (text[i] == 'g') m_text[i] = char_G;
      if (text[i] == 'h') m_text[i] = char_H;
      if (text[i] == 'i') m_text[i] = char_I;
      if (text[i] == 'j') m_text[i] = char_J;
      if (text[i] == 'k') m_text[i] = char_K;
      if (text[i] == 'l') m_text[i] = char_L;
      if (text[i] == 'm') m_text[i] = char_M;
      if (text[i] == 'n') m_text[i] = char_N;
      if (text[i] == 'o') m_text[i] = char_O;
      if (text[i] == 'p') m_text[i] = char_P;
      if (text[i] == 'q') m_text[i] = char_Q;
      if (text[i] == 'r') m_text[i] = char_R;
      if (text[i] == 's') m_text[i] = char_S;
      if (text[i] == 't') m_text[i] = char_T;
      if (text[i] == 'u') m_text[i] = char_U;
      if (text[i] == 'v') m_text[i] = char_V;
      if (text[i] == 'w') m_text[i] = char_W;
      if (text[i] == 'x') m_text[i] = char_X;
      if (text[i] == 'y') m_text[i] = char_Y;
      if (text[i] == 'z') m_text[i] = char_Z;
      if (text[i] == ' ') m_text[i] = char_SPACE;
    }

    if (add_new_line)
    {
      m_text[text_length + 1] = char_SPACE;
      m_character_length = text_length + 1;
    }
    else
    {
      m_character_length = text_length;
    }

    m_current_char = m_is_reverse ? 0 : m_character_length - 1;
  }

  void display_text()
  {
    write_to_buffer();
    
    draw_buffer_to_matrix();

    update_letter_position();
  }

private:
  void write_to_buffer()
  {
    // write to buffer
    for (uint8_t i = 0; i < 8; i++)
    {
      // get the current bit from current row
      uint8_t bitset = m_text[m_current_char].letter_rows[i];
      uint8_t bit = bitRead(bitset, m_current_width);
      uint8_t offset = m_is_reverse ? 0 : CHAR_WIDTH;

      Serial.println(m_current_width);

      // assign that bit the last bit in the buffer bitset
      bitWrite(m_bitset_buffer[i], offset, bit);
    }
  }

  void update_letter_position()
  {
    // shift to the next set of cells
    if (m_is_reverse) m_current_width--;
    else m_current_width++;

    // has the letter been fully created?
    bool has_letter_passed = m_is_reverse ? m_current_width == 0 : m_current_width > CHAR_WIDTH;

    if (has_letter_passed)
    {
      // reset width for the next character
      m_current_width = m_is_reverse ? CHAR_WIDTH : 0;

      // move to the next character
      if (m_is_reverse) m_current_char++;
      else m_current_char--;

      // has the entire text been iterated
      bool word_finished = m_is_reverse ? m_current_char == m_character_length : m_current_char < 0;

      if (word_finished)
      {
        // go back to the first character
        m_current_char = m_is_reverse ? 0 : m_character_length - 1;
      }
    }

    // moves characters
    for (uint8_t i = 0; i < 8; i++)
    {
      if (m_is_reverse) m_bitset_buffer[i] <<= 1;
      else m_bitset_buffer[i] >>= 1;
    }
  }

  void draw_buffer_to_matrix()
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      m_matrix->setRow(0, i, m_bitset_buffer[i]);
    }
  }

private:
  LedControl* m_matrix;
  CharMatrix m_text[MAX_CHARACTERS];
  uint8_t m_bitset_buffer[8];
  uint8_t m_current_width;
  int m_current_char;
  int m_character_length;
  bool m_is_reverse;
};

LedControl matrix = LedControl(12, 10, 11, 1);
TextDisplayer td = TextDisplayer(&matrix, true);

void setup()
{
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);

  Serial.begin(9600);

  td.apply_text("hello mother");
}

void loop()
{
  delay(100);

  td.display_text();
}