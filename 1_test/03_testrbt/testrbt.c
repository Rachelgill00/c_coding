#include <stdio.h>



// 키 값을 기준으로 다음 노드를 반환하는 함수
node_t *get_next_node(const rbtree *t, node_t *p)
{
  node_t *current = p->right;
  if (current == t->nil) // 오른쪽 자식이 없으면
  {
    current = p;
    while (1)
    {
      if (current->parent->right == current) // current가 오른쪽 자식인 경우
        current = current->parent;           // 부모 노드로 이동 후 이어서 탐색
      
      else
        return current->parent; // current가 왼쪽 자식인 경우 부모 리턴
    }
  }

  while (current->left != t->nil) // 왼쪽 자식이 있으면
    current = current->left;      // 왼쪽 끝으로 이동

  return current;
}

//如果删除具有要删除的键的节点，则该节点将被删除，另一个节点将填充其位置。
//删除 替换 delete 时消失的节点，作为 remove 的子节点 被指定为replace_node。
//replace_node 将替换 Remove。


//要删除的节点：如果 delete 的两个子节点都存在。
//remove：delete后继节点，即要删除的节点的右侧子树中的最小节点。
//replace_node：后继节点的子节点替换现有的移除位置。
//（后继节点始终没有左子节点，因此只有一个右子节点。

//要删除的节点：如果没有删除的子节点，或者只有一个子节点。
//remove：删除需要删除的节点。
//replace_node ： delete remove（ = delete ） 的子节点'替换现有位置'。
//（如果子节点不存在，则 nil 节点将替换它。)

int rbtree_erase(rbtree *t, node_t *delete)
{
  node_t *remove; // 트리에서 없어질 노드
  node_t *remove_parent, *replace_node;
  int is_remove_black, is_remove_left;

  // Step 1) delete 삭제 후 대체할 replace_node 찾기
  // Step 1-1) delete 노드의 자식이 둘인 경우: delete의 키를 후계자 노드의 키값으로 대체, 노드의 색은 delete의 색 유지
  if (delete->left != t->nil && delete->right != t->nil)
  {
    remove = get_next_node(t, delete); // 후계자 노드 (오른쪽 서브트리에서 가장 작은 노드)
    replace_node = remove->right;      // 대체할 노드: 지워질 노드인 후계자는 항상 왼쪽 자식이 없기 때문에, 자식이 있다면 오른쪽 자식 하나뿐임
    delete->key = remove->key;         // delete의 키를 후계자 노드의 키값으로 대체 (색은 변경 X)
  }
  else
  { // Step 1-2) delete 노드의 자식이 없거나 하나인 경우: delete 노드를 자식으로 대체, 노드의 색도 대체되는 노드의 색으로 변경
    remove = delete;
    // 대체할 노드: 자식이 있으면 자식노드로, 없으면 nil 노드로 대체
    replace_node = (remove->right != t->nil) ? remove->right : remove->left;
  }
  remove_parent = remove->parent;

  // Step 2) remove 노드 제거하기
  /* [CASE D1]: remove 노드가 루트인 경우 */
  if (remove == t->root)
  {
    t->root = replace_node;        // 대체할 노드를 트리의 루트로 지정
    t->root->color = RBTREE_BLACK; // 루트 노드는 항상 BLACK
    free(remove);
    return 0; // 불균형 복구 함수 호출 불필요 (제거 전 트리에 노드가 하나 혹은 두개이므로 불균형이 발생하지 않음)
  }

  // Step 2-1) 'remove의 부모'와 'remove의 자식' 이어주기
  is_remove_black = remove->color; // remove 노드 제거 전에 지워진 노드의 색 저장
  is_remove_left = remove_parent->left == remove;

  // Step 2-1-1) 자식 연결
  if (is_remove_left) // remove가 왼쪽 자식이었을 경우: remove 부모의 왼쪽에 이어주기
    remove_parent->left = replace_node;
  else // remove가 오른쪽 자식이었을 경우: remove 부모의 오른쪽에 이어주기
    remove_parent->right = replace_node;

  // Step 2-1-2) 부모도 연결 (양방향 연결)
  replace_node->parent = remove_parent;
  free(remove);

  /* [CASE D2~D6]: remove 노드가 검정 노드인 경우 */
  // Step 3) 불균형 복구 함수 호출
  if (is_remove_black)
    rbtree_erase_fixup(t, remove_parent, is_remove_left);
  return 0;
}

//如果被移除的节点 remove 是根节点或 BLACK，则违反了 RB 树的规则，从而导致不平衡。
//为了解决这种不平衡，它总共分为 6 个案例。

//case1:如果 remove 是 root
//将 replace_node 设置为根并将其更改为 BLACK。

//case2: bro, bro leftcild, bro rightchild all BLACK

// [CASE D3] bro is RED

 // [CASE D4] bro is BLACK, 형제의 가까운 자식이 RED, 형제의 더 먼 자식이 BLACK

 // [CASE D5] 형제가 BLACK, 형제의 더 먼 자식이 RED

 //case 4 (other side)

//case 5 (other side)

//case 2(other side)

 