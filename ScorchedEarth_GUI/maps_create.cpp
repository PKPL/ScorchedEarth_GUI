/*
PORTUGUESE TEAM

NUNO VALENTE

*/

#include "maps_create.h"


extern int map_layout [MAX_X][MAX_Y];


void test_maps_create(int map_layout [MAX_X][MAX_Y])
{

}

//void create_mountain_map(int map_layout[MAX_X][MAX_Y])
//{
//    srand( time( NULL ) );
//    //int map_layout [MAX_X][MAX_Y];
//    float result;
//    int resultInted;
//    int diversity;
//    int i, j;
//
//
//
//    int startSin = RandInt(10,40);
//    float compaction;
//    float push;
//    float high;
//
//    bool conditionX=false;
//
//
//    for(i = 0; i< MAX_X; i++)
//    {
//        for(j = 0; j<MAX_Y; j++)
//        {
//
//            map_layout [i][j]=0;
//
//        }
//    }
//    int x= 1;
//
//    while(conditionX==false)
//    {
//        diversity=0;
//        float compaction = RandInt(3,10); // od 1 do 15
//        float push = RandFloatDced(1,10);// od 0 do 2
//        float high = RandFloatDced(10,25); // od -3 do 3
//
//
//        for(i = 0; i< MAX_X; i++)
//        {
//            if(RandInt(0,2)==1)compaction =compaction + RandInt(-3,3);
//            else compaction =compaction - RandInt(-3,3);
//            result = (x*high)*sin((x*i*compaction)*PI/180+(PI*push*x))*10;
//            resultInted = (int)result;
//            if(MAX_Y -resultInted - startSin >0 && MAX_Y -resultInted - startSin <MAX_Y)
//                map_layout [i][MAX_Y -resultInted - startSin]=1;
//
//            if(i>0)
//            {
//                if(map_layout [i-1][MAX_Y -resultInted - startSin]!=1)diversity++;
//            }
//
//
//            x=x+x*0.1;
//
//        }
//
//        system("cls");
//        int u;
//
//        //filling matrix
//        for(i = 0; i< MAX_X; i++)
//        {
//            for(j = 0; j<MAX_Y; j++)
//            {
//
//                if(map_layout[i][j]==1)
//                {
//                    for(u = j; u<80; u++)
//                    {
//                        map_layout[i][u] = 1;
//                    }
//                }
//            }
//        }
//
//        for(i = 0; i< MAX_X; i++)
//        {
//
//            j=79;
//            if(map_layout [i][j]==1)
//            {
//                conditionX = true;
//                continue;
//            }
//            else
//            {
//                conditionX = false;
//                break;
//            }
//
//
//        }
//        if(diversity < 25) conditionX = false;
//    }
//
//}

void create_mountain_map(int map_layout[MAX_X][MAX_Y])
{
    int x, y;
    bool checkInteger = true;
    for (x = 0; x < MAX_X; x++)
    {
        for (y = 0; y < MAX_Y; y++)
        {
            if (map_layout[x][y] % 2 != 0 && map_layout[x][y] % 2 != 1) // is not integer
            {
                printf("Map generation error: Contents of array different than expected.\n");
                checkInteger = !checkInteger;
                break;
            }
        }
    }

    if (checkInteger)
    {
        int auxiliary_number, parity, number, finished_creating_map, is_continuation, number_alternative, free_space_height, will_have_to_create_compensation_unit;
        free_space_height = MAX_Y;
        free_space_height = 0.25 * free_space_height;
        finished_creating_map = 0;
        will_have_to_create_compensation_unit = 0;
        is_continuation = 0;

        /*For a mountain map*/
        int terrain_deformation_start, height_offset_high, height_offset_low, deformation_width, deformation_height, widthMedian, terrain_units_built, terrain_units_until_median, terrain_units_to_build, terrainUnitsAfterMedian;
        terrain_units_built = 0;
        height_offset_high = 0;
        height_offset_low = 0;
        new_rnd_seed();
        system("cls");
        printf("Map is being randomly generated. This may take a while sorry =]");

        do
        {
            number = (rand() % MAX_TERRAIN_INITIAL_HEIGHT_MOUNTAINS_MAP) + 1; /*defines the initial terrain height*/
        }
        while (number == 0);

        do
        {
            do
            {

                terrain_deformation_start = (rand() % MAX_DISTANCE_UNTIL_DEFORMATION_START) + 1; /*defines the max distance until a deformation appears*/
                /*This will loop for all the x coordinates at the same height, before the first deformation*/
            }
            while (terrain_deformation_start < 2);

            if (is_continuation == 1)
            {
                terrain_units_to_build = (terrain_deformation_start - 1);
                if (terrain_units_built + terrain_units_to_build > MAX_X)
                {
                    terrain_units_to_build = (MAX_X - terrain_units_built);
                }
                for (x = terrain_units_built; terrain_units_to_build > 0; x++)
                {
                    for (y = 0; y < number; y++)
                    {
                        map_layout[x][y] = 1; /*This will create a surface after a deformation*/ /*number is the last height built on*/
                    }
                    terrain_units_built++;
                    terrain_units_to_build--;
                }
            }
            else
            {
                for (x = 0; x < (terrain_deformation_start - 1); x++)
                {
                    for (y = 0; y < number; y++)
                    {
                        map_layout[x][y] = 1; /*This will create the surface line before the first deformation*/
                    }
                    terrain_units_built++;
                }
            }

            do
            {

                deformation_width = (rand() % MAX_WIDTH_DEFORMATION) + 1; /*defines the max width for the deformation. This will have to be an odd number for this implementation version*/
            }
            while (deformation_width % 2 == 0 || deformation_width < 5); /*Ensures the deformation has at least the width of 5 units, and the deformation width is an odd number*/

            do
            {

                deformation_height = (rand() % ((MAX_Y - free_space_height))) + 1; /*defines the max height for the deformation.*/
                /*For this implementation version, valleys may appear on a mountain, but valleys will never be forcefully created. This will change on a later revision*/
            }
            while (deformation_height < 2); /*We have hardcoded the minimum height to 2 to stop the [y] value from being 0 or -1*/

            if (deformation_height + number >= (MAX_Y - free_space_height))
            {
                do
                {
                    deformation_height -= (0.42 * deformation_height);
                }
                while (deformation_height + number >= (MAX_Y - free_space_height));

            }

            if (abs(number - deformation_height) > 15)
            {
                auxiliary_number = (rand() % 15) +1;
                parity = auxiliary_number % 2;
                if (parity != 0)
                {
                    deformation_height = number + auxiliary_number;
                }
                else
                {
                    if (number - auxiliary_number > 0)
                    {
                        deformation_height = number - auxiliary_number;
                    }
                    else
                    {
                        deformation_height = number + auxiliary_number;
                    }
                }
            }

            height_offset_high = deformation_height + HEIGHT_OFFSET;
            height_offset_low = deformation_height - HEIGHT_OFFSET;

            /*The following code prevents the deformation width to go outside map bounds, and if a new width is to be defined, it ensures it's an odd number*/
            if (deformation_width + terrain_units_built >= MAX_X && (MAX_X - terrain_units_built) % 2 != 0)
            {
                deformation_width = (MAX_X - terrain_units_built);
                finished_creating_map = 1; /*No more space for deformations after the current one*/
            }
            else if (deformation_width + terrain_units_built >= MAX_X && (MAX_X - terrain_units_built - 1) % 2 != 0 && (MAX_X - terrain_units_built - 1) != -1)
            {
                deformation_width = (MAX_X - terrain_units_built - 1); /*Now we have to build one unit in a straight line*/
                will_have_to_create_compensation_unit = 1;
                finished_creating_map = 1; /*No more space for deformations after the current one*/
            }
            else if (deformation_width + terrain_units_built >= MAX_X && (MAX_X - terrain_units_built - 1) % 2 != 0 && (MAX_X - terrain_units_built - 1) == -1)
            {
                deformation_width = 0;
                finished_creating_map = 1;
            }
            /*At this point we have found the width and height for the deformation*/
            /*We need to find the width's median now*/
            if (deformation_width != 0)
            {
                widthMedian = (deformation_width/2) + 1; /*In this implementation version, the median of the width will have the highest height*/
            }
            else
            {
                widthMedian = 0;
            }
            terrain_units_until_median = deformation_width - widthMedian;
            terrain_units_to_build = terrain_units_until_median;
            terrainUnitsAfterMedian = terrain_units_until_median;

            for (x = terrain_units_built; terrain_units_to_build > 0; x++) /*This loop creates terrain deformation before reaching the mountain top. This can either create a mountain or a valley on a mountain.*/
            {
                do
                {

                    number = rand() % (height_offset_high + 1); /*Gets a number from 0 to the max deformation height + the height_offset_high to be built.*/
                }
                while (number < height_offset_low || number > height_offset_high || number <= 0);

                for (y = 0; y < number; y++)
                {
                    map_layout[x][y] = 1;
                }
                terrain_units_built++;
                terrain_units_to_build--;
            }
            print_loading_status(terrain_units_built);
            /*Now we have reached the median width value, which will have the max height*/
            x = terrain_units_built; /*This step is only for us to know that x has the value of the units built, but this is not a necessary line as that is already the value x holds. This is just a reminder*/

            for (y = 0; y < deformation_height; y++)
            {
                map_layout[x][y] = 1;
            }
            terrain_units_built++;
            print_loading_status(terrain_units_built);
            /*Now the median value already has terrain*/
            /*We need to assign terrain to the remaining values of the deformation width*/

            terrain_units_to_build = terrainUnitsAfterMedian;

            for (x = terrain_units_built; terrain_units_to_build > 0; x++) /*This loop creates terrain deformation after reaching the mountain top. This can either create a mountain or a valley on a mountain.*/
            {
                do
                {

                    number_alternative = rand() % (height_offset_high + 1); /*Gets a number from 0 to the max deformation height + the height_offset_high to be built.*/
                }
                while (number_alternative < height_offset_low || number_alternative > height_offset_high || number_alternative <= 0);

                for (y = 0; y < number_alternative; y++)
                {
                    map_layout[x][y] = 1;
                }
                number = y + 1;
                terrain_units_built++;
                terrain_units_to_build--;
            }

            print_loading_status(terrain_units_built);

            if (will_have_to_create_compensation_unit == 1)
            {
                for (x = (MAX_X - 1); x < MAX_X; x++)
                {
                    for (y = 0; y < number; y++)
                    {
                        map_layout[x][y] = 1; /*Draws the last x unit of the map if the last deformation didn't include the last x position*/
                    }
                }
            }

            is_continuation = 1;
            /*This concludes the building of a deformation*/
        }
        while (finished_creating_map != 1);

        print_loading_status(100);
        srand(1);
    }
}

void new_rnd_seed()
{
    srand(time(NULL));
}

void print_loading_status(int x)
{
    system("cls");
    printf("Loading: %d%%", x);
    if (x == 100)
    {
        printf("\n\n\nPlease wait while the map is drawn. Thank you! :D");
        Sleep(1500);
    }
}


//int RandInt(int a, int b)
//{
//    int result =( rand() % b-a ) + a;
//    return result;
//}
//
//float RandFloatDced(int a, int b)
//{
//    //float result = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
//    float result =( rand() % b-a ) + a;
//    result = result/10;
//    return result;
//
//}
//

