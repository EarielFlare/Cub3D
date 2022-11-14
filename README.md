# Cub3D

Здесь представлен почти допиленный cub3D, точнее - парсер и рэйкастер. Результат представлен в виде minimap и player на ней.

Парсер такой себе, взят и немножко допилен. Основной упор сделан на алгоритм raycaster. Реализован на методах по [ссылке](https://permadi.com/1996/05/ray-casting-tutorial-1/#INTRODUCTION).
Для работы алгоритма использовались два массива по горизонтальным и вертикальным стенам, полученные из исходного массива чаров карты.

Для каждого луча вычисляется его уравнение (вида y = kx + b), а точнее коэффициент b, после чего в цикле происходит поиск пересечений со стенами (горизонтальными, затем вертикальными).

Полученные дистанции (до точек пересечения) сравниваются, берется минимальная, и по ней рисуется луч на карте. Дистанция - это искомая величина, которую можно использовать для вычисления высоты столбика пикселей для типа 3D вида (будет рыбий глаз, делаем корректировку по туториалу).

Также интерес представляет метод рендеринга. Обычно существует два подхода. Первый: делать рендер по нажатию кнопки перемещения. Второй: вызывать функцию рендера в цикле, используя mlx_loop_hook. Я сделал так: вызов функции рендера происходит по тику таймера (настройку таймера см. в main). По завершению каждого периода вызывается handler, устанавливающий флаг события (таймер досчитал). Функция, объявленная в mlx_loop_hook, постоянно сверяет флаг и в случае его установки в 1 вызывает callback функцию render_func. По окончанию рендеринга флаг сбрасывается и поднимается только по новому тику таймера. Такой подход позволяет получить стабильный FPS и не грузить процессор на полную задачей постоянной отрисовки стопяцот раз в секунду.

Надеюсь, хороший человек возьмет мой кодэ и допилит его до ума =)
