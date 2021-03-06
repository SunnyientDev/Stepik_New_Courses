# Задания SQL

## Задание 1

Со сколькими креативными агентствами мы работаем?

Креативным агентством считается тот партнер, у которого нет локаций для проведения квестов, но при этом они пишут сценарии, которые мы используем.

## Задание 2

Выведите название того партнера, на чьих локациях под руководством девушек операторов, среднее время прохождения квеста ниже, чем у всех остальных и укажите это время.

В случае неоднозначного ответа, выведите того партнера, у которого название лексикографически меньше. (лексикографически – значит меньше по алфавиту)

## Задание 3

У какого квеста (выпишите его quest_nm) разница доли состоявшихся квестов в январе и в феврале наибольшая по модулю?

Долей считать количество состоявшихся квестов поделить на количество заявленных. В случае наличия нескольких квестов, подходящих под условие, требуется вывести тот, у которого значение quest_rk больше.

# Задания по визуализации

Поговорим о проекте Тинькофф Квест.
Рассматриваем следующий процесс: заявители регистрируются на сайте Тинькофф Квест, где указывают свой возраст. Всех зарегистрированных называем клиентами.


В дальнейшем кто-то из них совершает с созданного аккаунта покупки сертификатов на квест. Будем называть это утилизацией. Число дней от регистрации на сайте до первой покупки будем называть скоростью утилизации.

В приложенном файле таблица со следующими полями:

client_id -- id клиента, зарегистрированного на сайте
birth_dt -- дата его рождения
reg_dttm -- дата и время регистрации на сайте данного клиента
purchase_id -- id покупки
purchase_dt -- дата покупки
purchase_amt -- сумма покупки

Если данные по покупке пустые -- клиент не совершил утилизации.

## Задание 1
Постройте диаграмму (или график), которая показывает, как менялось множество клиентов по возрасту с течением времени.
В ответ пришлите изображение диаграммы (или графика) и код (SQL/Python), с помощью которого вы его получили

## Задание 2
Постройте диаграмму (или график), которая показывает, как по возрастным сегментам отличается конверсия в утилизацию.
В ответ пришлите изображение диаграммы (или графика) и код (SQL/Python), с помощью которого вы его получили

## Задание 3
Постройте диаграмму (или график), которая показывает, как скорость утилизации влияет на размер первой покупки.
В ответ пришлите изображение диаграммы (или графика) и код (SQL/Python), с помощью которого вы его получили

# АБ-тесты (часть 1)

## Задание 1

Кейс
Тинькофф.Таргет - это агрегатор кэшбэков от партнеров (супермаркеты, магазины электроники, онлайн-магазины, заправки и т.п.).


Под каждого партнера собирается целевая аудитория и запускается таргет на ограниченный период, поэтому у каждого клиента свой набор офферов и они периодически меняются.





Механика: когда клиент совершает покупку по нашей карте в магазине X и у него есть оффер от этого партнера, он получает часть денег (какой-то фиксированный процент) за эту операцию обратно на карту.


Одна из основных целей этого сервиса - чтобы как можно больше операций клиентов проходили через офферы.


Например, если клиент хочет купить велосипед, то он сначала идет в наш сервис, смотрит есть ли у него кэшбэк в таком магазине и покупает велосипед по офферу.


Плохой сценарий: если у клиента нет подходящего оффера или клиент его не находит среди других (у каждого клиента в моменте 200-400 офферов)


Придумайте 2 кейса-гипотезы для достижения основной цели и опишите процесс проведения исследования и АВ теста для проверки этой гипотезы.

## Задание 2


Маркетологи тестировали тему email-письма (разным группам послали email с разными темами).


Целевой метрикой был процент открытий.


Какой теме стоит отдать предпочтение и почему? Объясните свое решение

## Задание 3


Маркетологи тестировали тему email-письма (разным группам послали email с разными темами).


Целевой метрикой был процент открытий.


Какой теме стоит отдать предпочтение и почему? Объясните свое решение

## Задание 4

Тестовой группе отправляется пуш с призывом совершить оплату, контрольной группе не отправляли.


Является ли различие статистически значимым при уровне значимости 1%? А при 5%?

## Задание 5

Хотим протестировать новую версию сайта. Ожидаем, что вырастет число регистраций.


Обычно дневная конверсия из захода на сайт в регистрацию - 50%. Хотим поймать изменение на 5 %-пунктов при уровне значимости 1% и мощности 80%.


Так же известно, что каждый день к нам на сайт приходит 100 уникальных пользователей.


Какой размер выборки нам нужен? Сколько дней требуется проводить АВ тест?

## Задание 6
Проводим обзвон клиентов (тест – звоним, контроль – нет).

Цель – чтобы клиент оставил заявку на продукт.


Средняя стоимость одного звонка 50 рублей (дозвонились или нет не важно), с одной заявки мы зарабатываем в среднем 180 рублей.


Проинтерпретируйте результаты АВ теста
