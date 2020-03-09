#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* station_name;
    size_t time_in_m;
} user_input;

typedef struct {
    char* name;
    size_t arrival_time_in_m;
    size_t departure_time_in_m;
} train_stop;

typedef struct {
    char* name;
    size_t start_time_in_m;
    size_t num_of_stops;
    train_stop** stops;
} train;

typedef struct {
    size_t num_of_trains;
    train** list;
} Trains;

void free_trains_list(Trains* trains_list) {
    for (size_t i = 0; i < trains_list->num_of_trains; i++) {
        free(trains_list->list[i]);
    }
    free(trains_list->list);
    free(trains_list);
}

void free_train(train* convoy) {
    for (size_t i = 0; i < convoy->num_of_stops; i++) {
        free(convoy->stops[i]->name);
        free(convoy->stops[i]);
    }
    free(convoy->stops);
    free(convoy->name);
    free(convoy);
}

size_t humantime_to_min(size_t h, size_t m) {
    return 60 * h + m;
}

Trains* create_trains_list(size_t number_of_trains) {
    Trains* t_list = (Trains* )malloc(sizeof(Trains));
    if (!t_list) {
        fprintf(stderr, "Malloc error on list\n");
        return 0;
    }
    t_list->num_of_trains = number_of_trains;
    t_list->list = (train** )malloc(sizeof(train*) * number_of_trains);
    if (!t_list->list) {
        free(t_list);
        fprintf(stderr, "Malloc error on trains array\n");
        return 0;
    }
    return t_list;
}

train* create_train(Trains* train_list, char* train_name, size_t h, size_t m, size_t number_of_stops) {
    train* convoy = (train* )malloc(sizeof(train));
    if (!convoy) {
        fprintf(stderr, "Malloc error on creating train structure\n");
        return NULL;
    }
    convoy->name = train_name;
    convoy->start_time_in_m = humantime_to_min(h, m);
    convoy->num_of_stops = number_of_stops;
    convoy->stops = (train_stop** )malloc(sizeof(train_stop*) * number_of_stops);
    if (!convoy->stops) {
        fprintf(stderr, "Malloc error on creating stops in train structure\n");
        free(convoy);
        return NULL;
    }
    for(size_t i = 0; i < number_of_stops; i++) {
        convoy->stops[i] = (train_stop* )malloc(sizeof(train_stop));
        if (!convoy->stops[i]) {
            for (size_t j = 0; j < i; j++) {
                free(convoy->stops[j]);
            }
            free(convoy->stops);
            free(convoy);
            fprintf(stderr, "Malloc error on stops in train\n");
            return NULL;
        }
    }
    return convoy;
    // convoy = train_list->list[train_list->size]
}

Trains* init_from_file(const char* path_file) {
    FILE* source_file = fopen(path_file, "r");
    if (!source_file) {
        fprintf(stderr, "Cannot open file\n");
        return NULL;
    }
    size_t number_of_trains = 0;
    if (fscanf(source_file, "%zu", &number_of_trains) != 1) {
        fprintf(stderr, "Error while reading init-file1\n");
        fclose(source_file);
        return NULL;
    }

    Trains* trains_list = create_trains_list(number_of_trains);
    if (!trains_list) {
        fprintf(stderr, "Error while reading init-file2\n");
        fclose(source_file);
        return NULL;
    }
    for (size_t i = 0; i < number_of_trains; i++) {
        char* train_name = (char *)malloc(64 * sizeof(char));
        size_t h = 0;
        size_t m = 0;
        size_t number_of_stops = 0;
        if (fscanf(source_file, "%s %zu %zu %zu", train_name, &h, &m, &number_of_stops) != 4) {
            fprintf(stderr, "Error while reading init-file3\n");
            fclose(source_file);
            free_trains_list(trains_list);
            return NULL;
        }
        train* convoy = create_train(trains_list, train_name, h, m, number_of_stops);
        if (!convoy) {
            fprintf(stderr, "Error while reading init-file4\n");
            fclose(source_file);
            free_trains_list(trains_list);
            return NULL;
        }
        size_t arrival_h, arrival_m, department_h, department_m = 0;
        for (size_t j = 0; j < number_of_stops; j++) {
            char* stop_name = (char *)malloc(64 * sizeof(char));
            size_t res = fscanf(source_file, "%s %zu %zu %zu %zu",
                    stop_name,
                    &arrival_h,
                    &arrival_m,
                    &department_h,
                    &department_m);
            if (res != 5) {
                fprintf(stderr, "Error while reading init-file5\n");
                fclose(source_file);
                free_trains_list(trains_list);
                return NULL;
            }
            convoy->stops[j]->name = stop_name;
            convoy->stops[j]->arrival_time_in_m = humantime_to_min(arrival_h, arrival_m);
            convoy->stops[j]->departure_time_in_m = humantime_to_min(department_h, department_m);
        }
        trains_list->list[i] = convoy;
    }
    fclose(source_file);
    return trains_list;
}

char input_char() {
    char c = '\0';
    int result = 0;
    do {
        result = scanf("%c", &c);
    } while (result != 1);
    return c;
}

char *input_string() {
    struct buffer {
        char *string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = input_char(), c != EOF && c != '\n') {
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                return NULL;
            }
            if (buf.string) {
                tmp = strcpy(tmp, buf.string);
                free(buf.string);
            }
            buf.string = tmp;
            buf.capacity = new_capacity;
        }
        buf.string[buf.size] = c;
        buf.string[buf.size + 1] = '\0';
        ++buf.size;
    }
    return buf.string;
}


user_input* read_input_user_data() {
    user_input* user = (user_input*) malloc(sizeof(user_input));
    if (!user) {
        return NULL;
    }

    printf("Input railway station name: ");
    char* station_name = input_string();
    user->station_name = station_name;

    printf("Input trip departure hours (0..23): ");
    int time_h = 0;
    if ((scanf("%d", &time_h) != 1) || (time_h < 0 || time_h > 23)) {
        fprintf(stderr, "Error while creating user structure\n");
        free(user);
        return NULL;
    }

    printf("Input trip departure minutes (0..59): ");

    int time_m = 0;
    if ((scanf("%d", &time_m) != 1) || (time_h < 0 || time_h > 59)) {
        fprintf(stderr, "Error while creating user structure\n");
        free(user);
        return NULL;
    }
    user->time_in_m = humantime_to_min((size_t )time_h, (size_t )time_m);
    printf("Searching for the nearest flight to %s at %d:%d...\n", station_name, time_h, time_m);
    return user;
}

void free_memory(Trains* trains_list) {
    for (size_t i = 0; i < trains_list->num_of_trains; i++) {
        for (size_t j = 0; j < trains_list->list[i]->num_of_stops; j++) {
            free(trains_list->list[i]->stops[j]->name);
            free(trains_list->list[i]->stops[j]);
        }
        free(trains_list->list[i]->stops);
        free(trains_list->list[i]->name);
        free(trains_list->list[i]);      // 63str
    }
    free(trains_list->list);     // 36str
    free(trains_list);
}

char* search_train(Trains* trains_list, char* station, size_t time) {
    size_t closest_time = 24 * 60;
    size_t minimal_arrival_time = 24 * 60;
    char* train = NULL;
    for (size_t i = 0; i < trains_list->num_of_trains; i++) {
        if (trains_list->list[i]->start_time_in_m > time) {
            for (size_t j = 0; j < trains_list->list[i]->num_of_stops; j++) {
                if ((!strcmp(trains_list->list[i]->stops[j]->name, station)) &&
                    ((trains_list->list[i]->start_time_in_m - time) <= closest_time) &&
                    ((trains_list->list[i]->stops[j]->arrival_time_in_m) < minimal_arrival_time)) {
                    train = trains_list->list[i]->name;
                    closest_time = trains_list->list[i]->start_time_in_m - time;
                    minimal_arrival_time = trains_list->list[i]->stops[j]->arrival_time_in_m;
                }
            }
        }
    }
    return train;
}

int main(int argc, char* argv[]) {
    char* path = "/home/ivan/technopark/C++/init.txt";
    Trains* trains_list = init_from_file(path);
    user_input* data = read_input_user_data();
    if (!data) {
        printf("Error in users input data\n");
        free_memory(trains_list);
        return 0;
    }
    char* train_name = search_train(trains_list, data->station_name, data->time_in_m);
    if (!train_name) {
        printf("Alert! There are no flight today\n");
    } else {
        printf("Alert! %s is the nearest train\n", train_name);
    }
    free(data->station_name);
    free(data);
    free_memory(trains_list);
    return 0;
}
