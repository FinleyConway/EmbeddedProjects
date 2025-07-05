#pragma once

#include <LedControl.h>

#include "matrix_characters.h"

class TextDisplayer
{
public:
    TextDisplayer(LedControl *matrix, bool is_reverse) : 
        m_matrix(matrix),
        m_is_reverse(is_reverse)
    {
        m_current_width = is_reverse ? c_character_width : 0;
    }

    void apply_text(const char *text, bool add_new_line = true)
    {
        int text_length = strlen(text);

        if (text_length > c_max_characters - 1) return;
        if (text_length <= 0) return;

        for (int i = 0; i < text_length; i++)
        {
            if (text[i] == 'a') m_text[i] = MCharacter::A;
            if (text[i] == 'b') m_text[i] = MCharacter::B;
            if (text[i] == 'c') m_text[i] = MCharacter::C;
            if (text[i] == 'd') m_text[i] = MCharacter::D;
            if (text[i] == 'e') m_text[i] = MCharacter::E;
            if (text[i] == 'f') m_text[i] = MCharacter::F;
            if (text[i] == 'g') m_text[i] = MCharacter::G;
            if (text[i] == 'h') m_text[i] = MCharacter::H;
            if (text[i] == 'i') m_text[i] = MCharacter::I;
            if (text[i] == 'j') m_text[i] = MCharacter::J;
            if (text[i] == 'k') m_text[i] = MCharacter::K;
            if (text[i] == 'l') m_text[i] = MCharacter::L;
            if (text[i] == 'm') m_text[i] = MCharacter::M;
            if (text[i] == 'n') m_text[i] = MCharacter::N;
            if (text[i] == 'o') m_text[i] = MCharacter::O;
            if (text[i] == 'p') m_text[i] = MCharacter::P;
            if (text[i] == 'q') m_text[i] = MCharacter::Q;
            if (text[i] == 'r') m_text[i] = MCharacter::R;
            if (text[i] == 's') m_text[i] = MCharacter::S;
            if (text[i] == 't') m_text[i] = MCharacter::T;
            if (text[i] == 'u') m_text[i] = MCharacter::U;
            if (text[i] == 'v') m_text[i] = MCharacter::V;
            if (text[i] == 'w') m_text[i] = MCharacter::W;
            if (text[i] == 'x') m_text[i] = MCharacter::X;
            if (text[i] == 'y') m_text[i] = MCharacter::Y;
            if (text[i] == 'z') m_text[i] = MCharacter::Z;
            if (text[i] == ' ') m_text[i] = MCharacter::SPACE;
        }

        if (add_new_line)
        {
            m_text[text_length + 1] = MCharacter::SPACE;
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
            uint8_t offset = m_is_reverse ? 0 : c_character_width;

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
        bool has_letter_passed = m_is_reverse ? m_current_width == 0 : m_current_width > c_character_width;

        if (has_letter_passed)
        {
            // reset width for the next character
            m_current_width = m_is_reverse ? c_character_width : 0;

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
    static const uint8_t c_character_width = 7;
    static const uint8_t c_character_height = 5;
    static const uint8_t c_max_characters = 255;

private:
    LedControl* m_matrix;
    CharMatrix m_text[c_max_characters];
    uint8_t m_bitset_buffer[8];
    uint8_t m_current_width;
    int m_current_char;
    int m_character_length;
    bool m_is_reverse;
};