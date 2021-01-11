#include <stdio.h>
#include <stdlib.h>
#define MAX 30

struct president {
  int numberOfVotes;
  char name[MAX];
};

struct voter {
  char name[MAX];
};

struct president candidate[MAX];
struct voter _voter[MAX];

void create_candidate(int count) {
  printf("\n\n\t** Candidate **\n\n");
  int i;
  for (i = 0; i < count; i++) {
    printf("--> Enter Name of Candidate No. %d : ", i + 1);
    scanf("%s", candidate[i].name);
  }
}

void create_voter(int count) {
  printf("\n\n\t** Voters **\n\n");
  int i;
  for (i = 0; i < count; i++) {
    printf("--> Enter Name of Voter No. %d : ", i + 1);
    scanf("%s", _voter[i].name);
  }
}

int main(int argc, char * argv[]) {
  int numberOfCandidate, numberOfVoters;
  int winnerPos, loserPos, round;

  void getNumberOfCandidates() {
    printf("\t--> Enter Number of Candidate : ");
    scanf("%d", & numberOfCandidate);
  }

  void getNumberOfVoters() {
    printf("\t--> Enter Number of Voters : ");
    scanf("%d", & numberOfVoters);
  }

  getNumberOfCandidates();
  while (numberOfCandidate < 5) {
    system("cls");
    printf("\n\t\t* minimal number of candidates is 5 *\n\n");
    getNumberOfCandidates();
  }
  system("cls");
  getNumberOfVoters();
  while (numberOfVoters < 10) {
    system("cls");
    printf("\n\t\t* minimal number of voters is 10 *\n\n");
    getNumberOfVoters();
  }

  system("cls");

  create_candidate(numberOfCandidate);
  create_voter(numberOfVoters);

  void print_list() {
    int i;
    system("cls");
    printf("\t|\tList of Candidates Round %d\t|\n\n", round);
    for (i = 0; i < numberOfCandidate; i++) {
      printf("\tVote for Candidate %s \t No.  %d nv : %d \n\n", candidate[i].name, i + 1, candidate[i].numberOfVotes);
    }
    printf("\n\n");
  }

  void resetNumberOfVotes() {
    int i;
    for (i = 0; i < numberOfCandidate; i++) {
      candidate[i].numberOfVotes = 0;
    }
  }

  void removeCandidate(int pos) {
    int i;
    for (i = pos; i < numberOfCandidate; i++) {
      candidate[i] = candidate[i + 1];
    }
    numberOfCandidate--;
  }

  void print_winner(int pos) {
    system("cls");
    printf("\n\n\n\t*|\t Winner is %s\t|*\n\n\n", candidate[pos].name);
  }

  int checkForPoint() {
    int i, j, dup = 0;
    for (i = 0; i < numberOfCandidate - 1; i++) {
      for (j = i + 1; j < numberOfCandidate; j++) {
        if (candidate[i].numberOfVotes == candidate[j].numberOfVotes) {
          dup++;
        }
      }
    }
    if (dup == 0) {
      int c;
      winnerPos = 0;
      loserPos = 0;
      for (c = 1; c < numberOfCandidate; c++) {
        if (candidate[c].numberOfVotes > candidate[winnerPos].numberOfVotes) {
          winnerPos = c;
        }
        if (candidate[c].numberOfVotes < candidate[loserPos].numberOfVotes) {
          loserPos = c;
        }
      }
    }
    return dup;
  }

  for (round = 1; round <= 3; round++) {
    do {
      print_list();
      int i = 0, voteNumber;
      while (i < numberOfVoters) {
        print_list();
        printf(" --> I'm Voter %s I vote for the candidate No : ", _voter[i].name);
        scanf("%d", & voteNumber);
        if (voteNumber > 0 && voteNumber <= numberOfCandidate) {
          candidate[voteNumber - 1].numberOfVotes++;
          i++;
        }
      }
      if (checkForPoint() != 0) {
        resetNumberOfVotes();
      }
    } while (checkForPoint() != 0);

    if (round != 3) {
      removeCandidate(loserPos);
      resetNumberOfVotes();
    }
  }
  print_winner(winnerPos);
}