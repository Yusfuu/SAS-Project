#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

struct president {
  int numberOfVotes;
  char name[MAX];
};

struct voter {
  char name[MAX];
};

struct president candidate[MAX];
struct president candidateAdmis[MAX];
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

void print_winner(int pos) {
  system("cls");
  printf("\n\n\n\t*|\t Winner is %s\t|*\n\n\n", candidate[pos].name);
}

int main(int argc, char * argv[]) {
  int numberOfCandidate, numberOfVoters, winnerPos, loserPos, tie, round = 1;

  void getNumberOfCandidates() {
    printf("\n\t--> Enter Number of Candidate : ");
    scanf("%d", & numberOfCandidate);
  }

  void getNumberOfVoters() {
    printf("\n\t--> Enter Number of Voters : ");
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
    printf("\t=========================================\n\n");
    printf("\t|\tList of Candidates Round %d\t|\n\n", round);
    printf("\t=========================================\n\n\n");

    for (i = 0; i < numberOfCandidate; i++) {
      printf("\t_________________________________________\n\n");
      printf("\t|  Vote for Candidate %s \t No. %d, nv:%d  |\n", candidate[i].name, i + 1, candidate[i].numberOfVotes);
    }
    printf("\t_________________________________________\n\n");
  }

  void doVote() {
    int i = 0, j, v, voteNumber;
    for (v = 0; v < numberOfCandidate; v++) {
      candidate[v].numberOfVotes = 0;
    }
    while (i < numberOfVoters) {
      print_list();
      printf(" --> I'm Voter %s I vote for the candidate No : ", _voter[i].name);
      scanf("%d", & voteNumber);
      if (voteNumber > 0 && voteNumber <= numberOfCandidate) {
        candidate[voteNumber - 1].numberOfVotes++;
        i++;
      }
    }
    // check if tie
    for (j = 0; j < numberOfCandidate - 1; j++) {
      if (candidate[0].numberOfVotes == candidate[j + 1].numberOfVotes) {
        tie++;
      }
    }
  }

  //round 1
  do {
    tie = 0;
    doVote();
  } while (tie == numberOfCandidate - 1);

  if (tie != numberOfCandidate) {
    int remaining = 0, j;
    for (j = 0; j < numberOfCandidate; j++) {
      if ((float) candidate[j].numberOfVotes / numberOfVoters * 100 >= 15) {
        candidateAdmis[remaining] = candidate[j];
        remaining++;
      }
    }
    numberOfCandidate = remaining;
    for (j = 0; j < numberOfCandidate; j++) {
      candidate[j] = candidateAdmis[j];
    }
    if (numberOfCandidate == 1) {
      print_winner(0);
    }
  }
  //round 1

  //round 2
  round++;
  do {
    tie = 0;
    doVote();
  } while (tie == numberOfCandidate - 1);

  if (tie != numberOfCandidate) {
    int c, i;
    for (c = 1; c < numberOfCandidate; c++) {
      if (candidate[c].numberOfVotes < candidate[loserPos].numberOfVotes) {
        loserPos = c;
      }
    }
    for (i = loserPos; i < numberOfCandidate; i++) {
      candidate[i] = candidate[i + 1];
    }
    numberOfCandidate--;
    if (numberOfCandidate == 1) {
      print_winner(0);
      return 0;
    }
  }
  //round 2

  //round 3
  round++;
  do {
    tie = 0;
    doVote();
  } while (tie == numberOfCandidate - 1);

  if (tie != numberOfCandidate) {
    int c;
    for (c = 1; c < numberOfCandidate; c++) {
      if (candidate[c].numberOfVotes > candidate[winnerPos].numberOfVotes) {
        winnerPos = c;
      }
    }
  }

  print_winner(winnerPos);
  //round 3

}
