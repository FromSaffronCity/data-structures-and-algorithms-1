import java.lang.String;
import java.lang.Comparable;


public class TreeNode implements Comparable {
    private String character;
    private int frequency;

    private TreeNode left;
    private TreeNode right;

    private String huffCode;

    public TreeNode(String character, int frequency) {
        this.character = character;
        this.frequency = frequency;
    }

    public void setLeft(TreeNode left) {
        this.left = left;
        return ;
    }

    public void setRight(TreeNode right) {
        this.right = right;
        return ;
    }

    public void setHuffCode(String huffCode) {
        this.huffCode = huffCode;
    }

    public String getCharacter() {
        return this.character;
    }

    public int getFrequency() {
        return this.frequency;
    }

    public TreeNode getLeft() {
        return this.left;
    }

    public TreeNode getRight() {
        return this.right;
    }

    @Override  /* implemented */
    public int compareTo(Object object) {
        TreeNode node = (TreeNode) object;
        return this.frequency - node.frequency;
    }

    @Override
    public String toString() {
        return this.character + " " + this.huffCode;
    }
}
