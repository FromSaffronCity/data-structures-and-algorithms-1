import java.util.Comparator;


public class LetterComparator implements Comparator<TreeNode> {
    @Override  /* implemented */
    public int compare(TreeNode node1, TreeNode node2) {
        return node1.getCharacter().compareTo(node2.getCharacter());
    }
}
