#include <stdio.h>
#include <string.h>

struct Player {
    int ballScores[12];
    char playerName[50];
    int totalScore;
};

// Function to validate the score entered by the player
int validateScore(int score) {
    if (score >= 0 && score <= 6) {
        return 1; // valid score
    }
    return 0; // invalid score
}

// Function to prompt the player to enter scores for 12 balls
void playGame(struct Player *player) {
    printf("Enter scores for %s (12 balls, between 0 and 6):\n", player->playerName);
    player->totalScore = 0;

    for (int i = 0; i < 12; i++) {
        int score;
        printf("Ball %d: ", i + 1);
        scanf("%d", &score);

        // Validate score
        if (validateScore(score)) {
            player->ballScores[i] = score;
            player->totalScore += score;
        } else {
            printf("Invalid score! Ball %d is disregarded.\n", i + 1);
            player->ballScores[i] = 0; // Assign 0 if the score is invalid
        }
    }
}

// Function to determine the winner based on total score
void findWinner(struct Player player1, struct Player player2) {
    if (player1.totalScore > player2.totalScore) {
        printf("\n%s wins with a score of %d!\n", player1.playerName, player1.totalScore);
    } else if (player2.totalScore > player1.totalScore) {
        printf("\n%s wins with a score of %d!\n", player2.playerName, player2.totalScore);
    } else {
        printf("\nIt's a tie! Both players scored %d.\n", player1.totalScore);
    }
}

// Function to display the match scoreboard
void displayMatchScoreboard(struct Player player1, struct Player player2) {
    printf("\nMatch Summary:\n");

    // Display Player 1's performance
    printf("\n%s's Scorecard:\n", player1.playerName);
    for (int i = 0; i < 12; i++) {
        printf("Ball %d: %d\n", i + 1, player1.ballScores[i]);
    }
    printf("Total Score: %d\n", player1.totalScore);
    printf("Average Score: %.2f\n", player1.totalScore / 12.0);

    // Display Player 2's performance
    printf("\n%s's Scorecard:\n", player2.playerName);
    for (int i = 0; i < 12; i++) {
        printf("Ball %d: %d\n", i + 1, player2.ballScores[i]);
    }
    printf("Total Score: %d\n", player2.totalScore);
    printf("Average Score: %.2f\n", player2.totalScore / 12.0);
}

int main() {
    struct Player player1, player2;

    // Get player names
    printf("Enter Player 1's name: ");
    fgets(player1.playerName, sizeof(player1.playerName), stdin);
    player1.playerName[strcspn(player1.playerName, "\n")] = '\0'; // Remove newline character

    printf("Enter Player 2's name: ");
    fgets(player2.playerName, sizeof(player2.playerName), stdin);
    player2.playerName[strcspn(player2.playerName, "\n")] = '\0'; // Remove newline character

    // Play the game
    playGame(&player1);
    playGame(&player2);

    // Display match scoreboard
    displayMatchScoreboard(player1, player2);

    // Determine the winner
    findWinner(player1, player2);

    return 0;
}
