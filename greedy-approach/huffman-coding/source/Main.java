import java.lang.String;
import java.util.Scanner;
import java.util.PriorityQueue;


public class Main {
    private static PriorityQueue<TreeNode> huffTree = new PriorityQueue<>(new LetterComparator());

    public static void traverseHuffmanTree(TreeNode root, String huffCode) {
        if(root == null) {
            return ;
        }

        if(root.getLeft() == null && root.getRight() == null) {
            root.setHuffCode(huffCode);
            huffTree.add(root);  /* nodes are arranged according to alphabetic order */
        }

        traverseHuffmanTree(root.getLeft(), huffCode + 0);  /* left traversal */
        traverseHuffmanTree(root.getRight(), huffCode + 1);  /* right traversal */

        return ;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();

        PriorityQueue<TreeNode> minHeap = new PriorityQueue<>(number);

        for(int i=0; i<number; i++) {
            String character = scanner.next();
            int frequency = scanner.nextInt();

            minHeap.add(new TreeNode(character, frequency));  /* MinHeap created */
        }

        TreeNode root = null;  /* creating Huffman Tree*/

        while(minHeap.size() > 1) {
            /* extracting the minimums */
            TreeNode left = minHeap.poll();
            TreeNode right = minHeap.poll();

            /* creating internal node */
            root = new TreeNode("?", left.getFrequency()+right.getFrequency());
            root.setLeft(left);
            root.setRight(right);

            minHeap.add(root);  /* adding internal node to minHeap */
        }

        traverseHuffmanTree(root, "");  /* creating Huffman or Prefix Code */

        System.out.println("\n" + "Output:" + "\n");

        while(huffTree.size() > 0) {
            System.out.println(huffTree.poll());
        }
    }
}
