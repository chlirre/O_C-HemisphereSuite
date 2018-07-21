class ClockSkip : public HemisphereApplet {
public:

    const char* applet_name() {
        return "ClockSkip";
    }

    void Start() {
        ForEachChannel(ch)
        {
            p[ch] = 100 - (25 * ch);
            trigger_countdown[ch] = 0;
        }
    }

    void Controller() {
        ForEachChannel(ch)
        {
            if (Clock(ch)) {
                int prob = p[ch] + Proportion(DetentedIn(ch), HEMISPHERE_MAX_CV, 50);
                if (random(1, 100) <= prob) {
                    ClockOut(ch);
                    trigger_countdown[ch] = 1667;
                }
            }

            if (trigger_countdown[ch]) trigger_countdown[ch]--;
        }
    }

    void View() {
        gfxHeader(applet_name());
        DrawSelector();
        DrawIndicator();
    }

    void ScreensaverView() {
        DrawSelector();
        DrawIndicator();
    }

    void OnButtonPress() {
        cursor = 1 - cursor;
    }

    void OnEncoderMove(int direction) {
        p[cursor] = constrain(p[cursor] += direction, 0, 100);
    }
        
    uint32_t OnDataRequest() {
        uint32_t data = 0;
        Pack(data, PackLocation {0,7}, p[0]);
        Pack(data, PackLocation {7,7}, p[1]);
        return data;
    }

    void OnDataReceive(uint32_t data) {
        p[0] = Unpack(data, PackLocation {0,7});
        p[1] = Unpack(data, PackLocation {7,7});
    }

protected:
    void SetHelp() {
        help[HEMISPHERE_HELP_DIGITALS] = "Clock Ch1, Ch2";
        help[HEMISPHERE_HELP_CVS]      = "p Mod Ch1, Ch2";
        help[HEMISPHERE_HELP_OUTS]     = "Clock Ch1, Ch2";
        help[HEMISPHERE_HELP_ENCODER]  = "Set p";
    }
    
private:
    int16_t p[2];
    int trigger_countdown[2];
    uint8_t cursor;
    
    void DrawSelector()
    {
        ForEachChannel(ch)
        {
            gfxPrint(0 + (31 * ch), 15, p[ch]);
            gfxPrint("%");
            if (ch == cursor) gfxCursor(0 + (31 * ch), 23, 30);
        }
    }    
    
    void DrawIndicator()
    {
        ForEachChannel(ch)
        {
            gfxBitmap(12 + (32 * ch), 45, 8, clock_icon);
            if (trigger_countdown[ch] > 0) gfxFrame(9 + (32 * ch), 42, 13, 13);
        }
    }

};


////////////////////////////////////////////////////////////////////////////////
//// Hemisphere Applet Functions
///
///  Once you run the find-and-replace to make these refer to ClockSkip,
///  it's usually not necessary to do anything with these functions. You
///  should prefer to handle things in the HemisphereApplet child class
///  above.
////////////////////////////////////////////////////////////////////////////////
ClockSkip ClockSkip_instance[2];

void ClockSkip_Start(int hemisphere) {
    ClockSkip_instance[hemisphere].BaseStart(hemisphere);
}

void ClockSkip_Controller(int hemisphere, bool forwarding) {
    ClockSkip_instance[hemisphere].BaseController(forwarding);
}

void ClockSkip_View(int hemisphere) {
    ClockSkip_instance[hemisphere].BaseView();
}

void ClockSkip_Screensaver(int hemisphere) {
    ClockSkip_instance[hemisphere].BaseScreensaverView();
}

void ClockSkip_OnButtonPress(int hemisphere) {
    ClockSkip_instance[hemisphere].OnButtonPress();
}

void ClockSkip_OnEncoderMove(int hemisphere, int direction) {
    ClockSkip_instance[hemisphere].OnEncoderMove(direction);
}

void ClockSkip_ToggleHelpScreen(int hemisphere) {
    ClockSkip_instance[hemisphere].HelpScreen();
}

uint32_t ClockSkip_OnDataRequest(int hemisphere) {
    return ClockSkip_instance[hemisphere].OnDataRequest();
}

void ClockSkip_OnDataReceive(int hemisphere, uint32_t data) {
    ClockSkip_instance[hemisphere].OnDataReceive(data);
}