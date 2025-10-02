#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex;

pthread_cond_t agent_condition;

pthread_cond_t smoker_conditions[3];

enum Ingredient { TOBACCO, PAPER, MATCHES };
const char* ingredient_names[] = {"TOBACCO", "PAPER", "MATCHES"};

bool ingredients_on_table[3] = {false, false, false};

void* agent(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        int choice = rand() % 3;

        if (choice == 0) {
            ingredients_on_table[PAPER] = true;
            ingredients_on_table[MATCHES] = true;
            printf("Agent places PAPER and MATCHES.\n");
            pthread_cond_signal(&smoker_conditions[TOBACCO]);
        } else if (choice == 1) {
            ingredients_on_table[TOBACCO] = true;
            ingredients_on_table[MATCHES] = true;
            printf("Agent places TOBACCO and MATCHES.\n");
            pthread_cond_signal(&smoker_conditions[PAPER]);
        } else {
            ingredients_on_table[TOBACCO] = true;
            ingredients_on_table[PAPER] = true;
            printf("Agent places TOBACCO and PAPER.\n");
            pthread_cond_signal(&smoker_conditions[MATCHES]);
        }

        pthread_cond_wait(&agent_condition, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* smoker(void* arg) {
    long id = (long)arg;
    enum Ingredient my_ingredient = (enum Ingredient)id;

    while (1) {
        pthread_mutex_lock(&mutex);

        pthread_cond_wait(&smoker_conditions[my_ingredient], &mutex);

        printf("Smoker with %s takes ingredients and is smoking.\n", ingredient_names[my_ingredient]);
        ingredients_on_table[0] = ingredients_on_table[1] = ingredients_on_table[2] = false;
        sleep(2);

        pthread_cond_signal(&agent_condition);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t agent_thread;
    pthread_t smoker_threads[3];
    long i;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&agent_condition, NULL);
    for (i = 0; i < 3; i++) {
        pthread_cond_init(&smoker_conditions[i], NULL);
    }

    pthread_create(&agent_thread, NULL, agent, NULL);
    for (i = 0; i < 3; i++) {
        pthread_create(&smoker_threads[i], NULL, smoker, (void*)i);
    }

    pthread_join(agent_thread, NULL);
    for (i = 0; i < 3; i++) {
        pthread_join(smoker_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&agent_condition);
    for (i = 0; i < 3; i++) {
        pthread_cond_destroy(&smoker_conditions[i]);
    }

    return 0;
}
