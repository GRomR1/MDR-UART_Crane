#ifndef __ELEMENT_H
#define __ELEMENT_H

/** \brief Элементы, принимающие или посылающие данные в BT-канал
 *
 *  Команды посылаемые от Пульта к КМУ: 0x01 - 0x7F
 *  Команды посылаемые от КМУ к Пульту: 0x80 - 0xFF
 */
 enum Element
{
    powerButton     = 0x01,     /**< Питание (вкл/выкл) (1/0) */
    lightButton     = 0x02,     /**< Свет (вкл/выкл) (1/0) */
    soundSignal     = 0x03,     /**< Гудок (вкл/выкл) (1/0) */
    speedButton     = 0x04,     /**< Скорость (медленно/быстро) (0/1..9) */
    pillarUp        = 0x05,     /**< Поворот стойки - по часовой стрелке (1..9) */
    pillarDown      = 0x06,     /**< Поворот стойки - против часовой стрелке (1..9) */
    derrickUp       = 0x07,     /**< Подъемная стрела - подъем (1..9) */
    derrickDown     = 0x08,     /**< Подъемная стрела - опускание (1..9) */
    outriggerUp     = 0x09,     /**< Выносная стрела - подъем (1..9) */
    outriggerDown   = 0x0A,     /**< Выносная стрела - опускание (1..9) */
    telescopicUp    = 0x0B,     /**< Телескопическая стрела - выдвижение (1..9) */
    telescopicDown  = 0x0C,     /**< Телескопическая стрела - втягивание (1..9) */
    hookUp          = 0x0D,     /**< Лебедка(крюк) - подъем (1..9) */
    hookDown        = 0x0E,     /**< Лебедка(крюк) - опускание (1..9) */
    leftCrutchUp    = 0x0F,     /**< Левая опора - подъем (1..9) */
    leftCrutchDown  = 0x10,     /**< Левая опора - опускание (1..9) */
    rightCrutchUp   = 0x11,     /**< Правая опора - подъем (1..9) */
    rightCrutchDown = 0x12,     /**< Правая опора - опускание (1..9) */

    powerStatus     = 0x80,     /**< Питание (вкл/выкл) (1/0) */
    lightStatus     = 0x81,     /**< Свет (вкл/выкл) (1/0) */                   
    highTemperature = 0x54,     /**< Перегрев ОЖ (нет/есть) (0/1) */																		//********* 0x82
    hookWarning     = 0x48,     /**< Ограничитель подъема (срабатывание/норм.работа) (1/0) */						//********* 0x83

		on     					= 0x31,     /**< включить */																												//********* 0x01
		off    					= 0x30,     /**< выключить */																												//********* 0x00
    incorrectCommand = 0xFF,    /**< Некорректная команда */
};
/*******************************************************************/

#endif