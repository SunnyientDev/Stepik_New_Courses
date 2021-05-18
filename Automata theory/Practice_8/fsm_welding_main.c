#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "fsm_welding.h"

char *engine_state_string(enum EngineState state){
    switch (state){
        case ENGINE_WELDING_OFF:
            return "ENGINE_WELDING_OFF";
        case ENGINE_WELDING_GAS_ON:
            return "ENGINE_WELDING_GAS_ON";
        case ENGINE_WELDING_RUN_AUTOMATE:
            return "ENGINE_WELDING_RUN_AUTOMATE";
        case ENGINE_WELDING_RUNNING:
            return "ENGINE_WELDING_RUNNING";
        case ENGINE_WELDING_COMPLETE_AUTOMATE:
            return "ENGINE_WELDING_COMPLETE_AUTOMATE";
        case ENGINE_WELDING_GAS_STABLE:
            return "ENGINE_WELDING_GAS_STABLE";
        case ENGINE_WELDING_GAS_OFF:
            return "ENGINE_WELDING_GAS_OFF";
        case ENGINE_WELDING_COMPLETE:
            return "ENGINE_WELDING_COMPLETE";
        default:
            return "UNKNOWN";
    }
}

char *automate_state_string(enum AutomateState state){
    switch(state){
        case AUTOMATE_OFF:
            return "AUTOMATE_OFF";
        case AUTOMATE_T_N:
            return "AUTOMATE_T_N";
        case AUTOMATE_WELDING:
            return "AUTOMATE_WELDING";
        case AUTOMATE_T_C:
            return "AUTOMATE_T_C";
        case AUTOMATE_COMPLETE:
            return "AUTOMATE_COMPLETE";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char **argv){
    bool running = true;
    int tick = 0;
    enum InputSignal signal = WELDING_OFF;
    struct Engine engine = {ENGINE_WELDING_OFF, 0, 0, 0};

    engine_init(&engine);

    while(running){
        ++tick;

        fprintf(stdout, "[%08d] ENGINE[%s] = %f, SIGNAL: [%s], I[%s] = %f, U[%s] = %f, V[%s] = %f \n",
            tick,
            engine_state_string(engine.state),
            engine.value,
            signal == WELDING_OFF ? "WELDING_OFF" : "WELDING_ON",
            automate_state_string(engine.automate[AUTOMATE_I].state),
            engine.automate[AUTOMATE_I].value,
            automate_state_string(engine.automate[AUTOMATE_U].state),
            engine.automate[AUTOMATE_U].value,
            automate_state_string(engine.automate[AUTOMATE_V].state),
            engine.automate[AUTOMATE_V].value);

        if(tick >= 200){
            signal = WELDING_ON;
        } else if (engine.state == ENGINE_WELDING_RUNNING) {
            signal = WELDING_OFF;
        }
        engine_tick(&engine, signal);
        running = !(engine.state == ENGINE_WELDING_COMPLETE);
    }

    engine_reset(&engine);
    return EXIT_SUCCESS;
}