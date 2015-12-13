#include "commandexecutor.h"

#include <Windows.h>

#include <QDebug>
#include <QHash>

namespace {

// See https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
QHash<QString, WORD> windows_key_kodes
{
    {QString("LEFT")     , VK_LEFT},
    {QString("RIGHT")    , VK_RIGHT},
    {QString("UP")       , VK_UP},
    {QString("DOWN")     , VK_DOWN},
    {QString("PAGE_UP")  , VK_PRIOR},
    {QString("PAGE_DOWN"), VK_NEXT},
    {QString("HOME")     , VK_HOME},
    {QString("END")      , VK_END},
    {QString("DEL")      , VK_DELETE},
    {QString("INSERT")   , VK_INSERT},

    {QString("ESC")      , VK_ESCAPE},
    {QString("ENTER")    , VK_RETURN},
    {QString("BACKSPACE"), VK_BACK},
    {QString("TAB")      , VK_TAB},
    {QString("CTRL")     , VK_CONTROL},
    {QString("SHIFT")    , VK_SHIFT},
    {QString("ALT")      , VK_MENU},
    {QString("SUPER")    , VK_LWIN},
    {QString("SPACE")    , VK_SPACE},
    {QString("CAPS_LOCK"), VK_CAPITAL},

    {QString("~")        , VK_OEM_3},
    {QString("1")        , 0x31},
    {QString("2")        , 0x32},
    {QString("3")        , 0x33},
    {QString("4")        , 0x34},
    {QString("5")        , 0x35},
    {QString("6")        , 0x36},
    {QString("7")        , 0x37},
    {QString("8")        , 0x38},
    {QString("9")        , 0x39},
    {QString("0")        , 0x30},
    {QString("-")        , VK_OEM_MINUS},
    {QString("=")        , VK_OEM_PLUS},

    {QString("A")        , 0x41},
    {QString("B")        , 0x42},
    {QString("C")        , 0x43},
    {QString("D")        , 0x44},
    {QString("E")        , 0x45},
    {QString("F")        , 0x46},
    {QString("G")        , 0x47},
    {QString("H")        , 0x48},
    {QString("I")        , 0x49},
    {QString("J")        , 0x4A},
    {QString("K")        , 0x4B},
    {QString("L")        , 0x4C},
    {QString("M")        , 0x4D},
    {QString("N")        , 0x4E},
    {QString("O")        , 0x4F},
    {QString("P")        , 0x50},
    {QString("Q")        , 0x51},
    {QString("R")        , 0x52},
    {QString("S")        , 0x53},
    {QString("T")        , 0x54},
    {QString("U")        , 0x55},
    {QString("V")        , 0x56},
    {QString("W")        , 0x57},
    {QString("X")        , 0x58},
    {QString("Y")        , 0x59},
    {QString("Z")        , 0x5A},

    {QString("[")        , VK_OEM_4},
    {QString("]")        , VK_OEM_6},
    {QString("\\")       , VK_OEM_5},
    {QString(";")        , VK_OEM_1},
    {QString("'")        , VK_OEM_7},
    {QString(",")        , VK_OEM_COMMA},
    {QString(".")        , VK_OEM_PERIOD},
    {QString("/")        , VK_OEM_2},
};

QHash<QString, DWORD> mouse_button_press_codes
{
    {QString("LEFT")  , MOUSEEVENTF_LEFTDOWN},
    {QString("RIGHT") , MOUSEEVENTF_RIGHTDOWN},
    {QString("MIDDLE"), MOUSEEVENTF_MIDDLEDOWN},
};

QHash<QString, DWORD> mouse_button_release_codes
{
    {QString("LEFT")  , MOUSEEVENTF_LEFTUP},
    {QString("RIGHT") , MOUSEEVENTF_RIGHTUP},
    {QString("MIDDLE"), MOUSEEVENTF_MIDDLEUP},
};

INPUT new_keyboard_event
{
   INPUT_KEYBOARD,
   {
       0,
       0,
       0,
       0,
       0,
       0
   }
};

INPUT new_mouse_event
{
   INPUT_MOUSE,
   {
       0,
       0,
       0,
       0,
       0,
       0
   }
};
} // anonymous

void CommandExecutor::execKey(CommandExecutor::KeyCommandType type, const QString &key)
{
    if (!windows_key_kodes.contains(key))
    {
        qDebug() << "Unimplemented key:" << key;
        return;
    }
    new_keyboard_event.ki.wVk = windows_key_kodes[key];
    if (type == KEY_UP)
    {
        new_keyboard_event.ki.dwFlags = KEYEVENTF_KEYUP;
    }
    else // KEY_DOWN
    {
        new_keyboard_event.ki.dwFlags = 0;
    }
    if (SendInput(1, &new_keyboard_event, sizeof new_keyboard_event) != 1)
    {
        qDebug() << "Key: SendInput error:" << GetLastError();
    }
}

void CommandExecutor::execMouseKey(CommandExecutor::MouseKeyCommandType type, const QString &button)
{
    if (!mouse_button_press_codes.contains(button)) // mouse_button_release_codes has the same codes
    {
        qDebug() << "Unimplemented mouse button:" << button;
        return;
    }
    if (type == BUTTON_PRESS)
    {
        new_mouse_event.mi.dwFlags = mouse_button_press_codes[button];
    }
    else // BUTTON_RELEASE
    {
        new_mouse_event.mi.dwFlags = mouse_button_release_codes[button];
    }
    new_mouse_event.mi.mouseData = 0;
    POINT pos;
    GetCursorPos(&pos);
    new_mouse_event.mi.dx = pos.x;
    new_mouse_event.mi.dy = pos.y;
    if (SendInput(1, &new_mouse_event, sizeof new_mouse_event) != 1)
    {
        qDebug() << "MouseKey: SendInput error:" << GetLastError();
    }
}

void CommandExecutor::mouseMove(int dx, int dy)
{
    new_mouse_event.mi.dx = dx * mouse_move_speed;
    new_mouse_event.mi.dy = dy * mouse_move_speed;
    new_mouse_event.mi.mouseData = 0;
    new_mouse_event.mi.dwFlags = MOUSEEVENTF_MOVE;
    if (SendInput(1, &new_mouse_event, sizeof new_mouse_event) != 1)
    {
        qDebug() << "MouseMove: SendInput error:" << GetLastError();
    }
}

void CommandExecutor::mouseWheel(int dx)
{
    POINT pos;
    GetCursorPos(&pos);
    new_mouse_event.mi.dx = pos.x;
    new_mouse_event.mi.dy = pos.y;
    new_mouse_event.mi.dwFlags = MOUSEEVENTF_WHEEL;
    new_mouse_event.mi.mouseData = dx;
    if (SendInput(1, &new_mouse_event, sizeof new_mouse_event) != 1)
    {
        qDebug() << "MouseWheel: SendInput error:" << GetLastError();
    }
}
