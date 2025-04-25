#include <kn/KrakenEngine.hpp>
#include "keybinds.hpp"

void setBinds(){
    kn::input::bind("up",
    {
        kn::InputAction(kn::S_w),
        kn::InputAction(kn::S_UP),
    }
    );

    kn::input::bind("left",
    {
        kn::InputAction(kn::S_a),
        kn::InputAction(kn::S_LEFT),
    }
    );

    kn::input::bind("down",
    {
        kn::InputAction(kn::S_s),
        kn::InputAction(kn::S_DOWN),
    }
    );

    kn::input::bind("right",
    {
        kn::InputAction(kn::S_d),
        kn::InputAction(kn::S_RIGHT),
    }
    );
    kn::input::bind("jump",
    {
        kn::InputAction(kn::S_SPACE),
    }
    );



    kn::input::bind("changemode",
    {
        kn::InputAction(kn::S_i),
    });


    // kn::input::bind("addGroup",
    // {
    //     kn::InputAction(kn::S_p),
    // });


    // kn::input::bind("delGroup",
    // {
    //     kn::InputAction(kn::S_o),
    // });


    kn::input::bind("addPolygon",
    {
        kn::InputAction(kn::S_p),
    });


    kn::input::bind("delPolygon",
    {
        kn::InputAction(kn::S_o),
    });

    kn::input::bind("leftClick",
    {
        kn::InputAction(kn::M_LEFT),
    });
    kn::input::bind("rightClick",
    {
        kn::InputAction(kn::M_RIGHT),
    });


    kn::input::bind("return",
    {
        kn::InputAction(kn::S_RETURN),
    });

}
