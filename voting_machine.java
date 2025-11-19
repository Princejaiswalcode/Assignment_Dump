import java.io.FileOutputStream;
import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;

class Candidate {
    private String name;
    private int votes;

    public Candidate(String name) {
        this.name = name;
        this.votes = 0;
    }

    public String getname() {
        return name;
    }

    public int getvotes() {
        return votes;
    }

    public void addvote() {
        votes++;
    }
}

public class voting_machine 
{
    private static Candidate[] candidates;

    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        candidates = new Candidate[3];
        candidates[0] = new Candidate("Prince");
        candidates[1] = new Candidate("Millind");
        candidates[2] = new Candidate("Deepak sir");
        boolean b=true;
        while (b) {
            System.out.println("\n======================= Voting Machine =======================");
            System.out.println("1. Cast a vote");
            System.out.println("2. Show the result");
            System.out.println("3. Save result to file");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            try {
                int choice = sc.nextInt();
                switch (choice) {
                    case 1:
                        cast_vote(sc);
                        break;
                    case 2:
                        show_result();
                        break;
                    case 3:
                        save_result_to_file();
                        break;
                    case 4:
                        b=false;
                        System.out.println("exiting........dhanyawad!!");
                        break;
                    default:
                        System.out.println("invalid choice,try again!");
                }
            } catch (InputMismatchException e) {
                System.out.println("invalid input,please enter numbers only.");
                sc.nextLine();
            }
        }
        sc.close();
    }


    private static void cast_vote(Scanner sc) {
        System.out.println("\n------------------------------------cast your vote------------------------------------");
        for (int i = 0; i < candidates.length; i++) {
            System.out.println((i + 1) + ". " + candidates[i].getname());
        }

        System.out.print("choose candidate number: ");
        try {
            int choice = sc.nextInt();
            if (choice >= 1 && choice <= candidates.length) {
                candidates[choice - 1].addvote();
                System.out.println("Voted successfully for " + candidates[choice - 1].getname());
            } else {
                System.out.println("invalid candidate choice");
            }
        } catch (InputMismatchException e) {
            System.out.println("invalid input,please enter a number.");
            sc.nextLine();
        }
    }


    private static void show_result() {
        System.out.println("\n------------------------------------voting result------------------------------------");
        for (Candidate a : candidates) {
            System.out.println(a.getname() + " : " + a.getvotes() + " votes");
        }
    }



    private static void save_result_to_file() {
        try {
            FileOutputStream ou = new FileOutputStream("voting_results.txt");
            
            for (Candidate a : candidates) {
                String line = a.getname() + " : " + a.getvotes() + " votes\n";
                ou.write(line.getBytes());
            }

            ou.close();
            System.out.println("result saved to voting_results.txt successfully");
        } catch (IOException e) {
            System.out.println("error while saving result: " + e.getMessage());
        }
    }
}

