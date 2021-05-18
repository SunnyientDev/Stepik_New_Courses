#include <stdbool.h>
#include "fsm_welding.h"

//время, на которое будет увеличиваться число шагов
#define TIME_DELTA(t) ((t) * 5)

//Функция для работы с маленькими автоматами
static void automate_tick(struct Automate *automate, enum InputSignal signal) {
    
    switch (automate->state){
        //автомат выключен
        case AUTOMATE_OFF: {
            if(signal == WELDING_ON){
                automate->state = AUTOMATE_T_N;
                automate->time_tick = 0;
            }
            break;
        }

        //насыщение
        case AUTOMATE_T_N: {
            if(signal == WELDING_ON){
                automate->time_tick++;
                if(automate->time_tick >= automate->time_n){
                    automate->state = AUTOMATE_WELDING;
                } else {
                    automate->value++;
                }
            } else {
                automate->state = AUTOMATE_T_C; //переходим в спад
            }
            break;
        }

        //сварка
        case AUTOMATE_WELDING: {
            if(signal == WELDING_ON){
                automate->state = AUTOMATE_WELDING;
            } else {
                automate->state = AUTOMATE_T_C;
                automate->time_tick = 0;
            }
            break;
        }

        //спад
        case AUTOMATE_T_C: {
            if(signal == WELDING_ON){
                automate->time_tick++;
                if(automate->time_tick >= automate->time_c){
                    automate->state = AUTOMATE_COMPLETE;
                } else{
                    automate->value--;
                }
            }
            break;
        }

        //завершение
        case AUTOMATE_COMPLETE: {
            automate->state = AUTOMATE_COMPLETE;
            break;
        }    
    }
}

void engine_init(struct Engine *engine) {
    engine_reset(engine);
}

void engine_reset(struct Engine *engine) {
    engine->state = ENGINE_WELDING_OFF;

    engine->time_tick = 0;
    engine->time_n = TIME_DELTA(10);
    engine->time_c = TIME_DELTA(10);
    engine->time_g = TIME_DELTA(5);
    engine->value = 0; //начальное значение = 0

    //Ток
    engine->automate[AUTOMATE_I].state = AUTOMATE_OFF;
    engine->automate[AUTOMATE_I].time_tick = 0;
    engine->automate[AUTOMATE_I].time_n = TIME_DELTA(8);
    engine->automate[AUTOMATE_I].time_c = TIME_DELTA(8);
    engine->automate[AUTOMATE_I].value = 0;

    //Напряжение
    engine->automate[AUTOMATE_U].state = AUTOMATE_OFF;
    engine->automate[AUTOMATE_U].time_tick = 0;
    engine->automate[AUTOMATE_U].time_n = TIME_DELTA(5);
    engine->automate[AUTOMATE_U].time_c = TIME_DELTA(5);
    engine->automate[AUTOMATE_U].value = 0;

    //Скорость подачи проволоки
    engine->automate[AUTOMATE_V].state = AUTOMATE_OFF;
    engine->automate[AUTOMATE_V].time_tick = 0;
    engine->automate[AUTOMATE_V].time_n = TIME_DELTA(3);
    engine->automate[AUTOMATE_V].time_c = TIME_DELTA(3);
    engine->automate[AUTOMATE_V].value = 0;
}

//Основной рабочий автомат по сварке
void engine_tick(struct Engine *engine, enum InputSignal signal) {
    switch (engine->state){
        
        //начало и конец сварки
        case ENGINE_WELDING_OFF: {
            if(signal == WELDING_ON){
                engine->state = ENGINE_WELDING_GAS_ON;
                engine->time_tick = 0;
            } else {
                engine->state = ENGINE_WELDING_OFF;
            }
            break;
        }

        //подача газа
        case ENGINE_WELDING_GAS_ON: {
            if(signal == WELDING_ON){
                engine->time_tick++;
                if(engine->time_tick >= engine->time_n){
                    engine->state = ENGINE_WELDING_RUN_AUTOMATE;
                    engine->time_tick = 0;
                } else {
                    engine->value--;
                }
            } else {
                engine->state = ENGINE_WELDING_COMPLETE_AUTOMATE;
                engine->time_tick = 0;
            }
            break;
        }

        //запуска автомата
        case ENGINE_WELDING_RUN_AUTOMATE: {
            if(signal == WELDING_ON){
                int i;
                bool welding = true;
                for(i = 0; i < AUTOMATE_COUNT; ++i){ 
                    automate_tick(&engine->automate[i], signal); 
                    welding = welding && (engine->automate[i].state == AUTOMATE_WELDING);
                }
                
                if(welding){
                    //мы готовы начать сварку
                    engine->state = ENGINE_WELDING_RUNNING;
                } else {
                    //нет, не готовы
                    engine->state = ENGINE_WELDING_RUN_AUTOMATE;
                }

            } else {
                engine->state = ENGINE_WELDING_COMPLETE_AUTOMATE;
                engine->time_tick = 0;
            }
            break;
        }

        //сварка
        case ENGINE_WELDING_RUNNING: {
            if(signal == WELDING_OFF){
                engine->state = ENGINE_WELDING_COMPLETE_AUTOMATE;
            }
            break;
        }

        //завершаем работу
        case ENGINE_WELDING_COMPLETE_AUTOMATE: {
            int i;
            bool complete = true;

            //как только все автоматы завершили свою работу
            for(i = 0; i < AUTOMATE_COUNT; ++i){ 
                automate_tick(&engine->automate[i], signal); 
                complete = complete && (engine->automate[i].state == AUTOMATE_COMPLETE);
            }

            //переходим в режим стабилизации/какое-то время подаем газ
            if(complete){
                engine->state = ENGINE_WELDING_GAS_STABLE;
                engine->time_tick = 0;
            }
            break;
        }

        //стабилизируем газ
        case ENGINE_WELDING_GAS_STABLE: {
            engine->time_tick++;
            if(engine->time_tick >= engine->time_g){
                engine->state = ENGINE_WELDING_GAS_OFF;
                engine->time_tick = 0;
            }
            break;
        }

        //выключаем газ
        case ENGINE_WELDING_GAS_OFF: {
            engine->time_tick++;
            if(engine->time_tick >= engine->time_c){
                engine->state = ENGINE_WELDING_COMPLETE;
                engine->time_tick = 0;
            } else {
                engine->value--;
            }
            break;
        }

        //Ура! Завершилось
        case ENGINE_WELDING_COMPLETE: {
            break;
        }
    }
}