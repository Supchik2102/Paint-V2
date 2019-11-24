#include <TXLib.h>

struct MenuButton

{

    bool isEnd_;

    void (*func_) ();

    const char * text_;

    bool stroke_;

};

struct Menu

{

    int x_;
    int y_;
    int width_;
    int height_;

    const char * titleText_;
    const char * titleFont_;

    const char * font_;

    COLORREF color_;
    COLORREF textColor_;
    COLORREF titleColor_;
    COLORREF titleTextColor_;
    COLORREF strokeColor_;

    HDC dc_;

    MenuButton * buttons_;

    int buttonsAmount () const;

    void draw () const;

    int check ();

};

int Menu::buttonsAmount () const

{

    for (int n = 0; true; n++)

    {

        if (buttons_[n].isEnd_ == true)

        {

            return n;

        }

    }

}

void Menu::draw () const

{

    txSetColor (color_, 0, dc_);
    txSetFillColor (color_, dc_);
    txRectangle (x_, y_, x_ + width_, y_ + height_, dc_);

    txSetColor (titleColor_, 0, dc_);
    txSetFillColor (titleColor_, dc_);
    txRectangle (x_, y_ - 25, x_ + width_, y_, dc_);

    txSetColor (titleTextColor_, 0, dc_);
    txSelectFont (titleFont_, 21, -1, FW_DONTCARE, false, false, false, 0, dc_);
    txTextOut (x_ + 2, y_ - 23, titleText_, dc_);

    int amount = buttonsAmount ();

    for (int n = 0; n < amount; n++)

    {

        int x = x_;
        int y = y_ + n * 25;
        int x1 = x + width_;
        int y1 = y_ + (n + 1) * 25;

        if (buttons_[n].stroke_)

        {

            txSetColor (strokeColor_, 0, dc_);
            txSetFillColor (strokeColor_, dc_);
            txRectangle (x, y, x1, y1, dc_);

            txSetColor (color_, 0, dc_);
            txSetFillColor (color_, dc_);
            txRectangle (x, y + 1, x1, y1 - 1, dc_);

        }

        else

        {

            txSetColor (color_, 0, dc_);
            txSetFillColor (color_, dc_);
            txRectangle (x, y, x1, y1, dc_);

        }

        txSetColor (textColor_, 0, dc_);
        txSelectFont (font_, 21, -1, FW_DONTCARE, false, false, false, 0, dc_);
        txTextOut (x + 2, y + 2, buttons_[n].text_, dc_);

    }

}

int Menu::check ()

{

    int amount = buttonsAmount ();

    POINT mPos = txMousePos ();

    for (int n = 0; n < amount; n++)

    {

        int x = x_;
        int y = y_ + n * 25;
        int x1 = x + width_;
        int y1 = y_ + (n + 1) * 25;

        if (mPos.x >= x && mPos.x < x1 && mPos.y >= y && mPos.y < y1)

        {

            buttons_[n].stroke_ = true;

            if (txMouseButtons () == 1)

            {

                if (buttons_[n].func_)

                {

                    buttons_[n].func_ ();

                }

                return n;

            }

        }

        else

        {

            buttons_[n].stroke_ = false;

        }

    }

}
