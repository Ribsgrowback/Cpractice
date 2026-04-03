from __future__ import annotations

from pathlib import Path

from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle, getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.pdfmetrics import registerFontFamily
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer


ROOT = Path(r"C:\Users\Administrator\Desktop\project3\Codexslot\docker\data_structures_docker\Data-Structures")
FONT_DIR = Path(r"C:\Users\Administrator\Desktop\project3\Codexslot\assets\fonts")


def register_fonts() -> None:
    regular = FONT_DIR / "NanumGothic-Regular.ttf"
    bold = FONT_DIR / "NanumGothic-Bold.ttf"
    pdfmetrics.registerFont(TTFont("NanumGothic", str(regular)))
    pdfmetrics.registerFont(TTFont("NanumGothicBold", str(bold)))
    registerFontFamily("NanumGothic", normal="NanumGothic", bold="NanumGothicBold")


def build_styles():
    sample = getSampleStyleSheet()
    title = ParagraphStyle(
        "TitleKo",
        parent=sample["Title"],
        fontName="NanumGothicBold",
        fontSize=20,
        leading=26,
        spaceAfter=10,
    )
    heading = ParagraphStyle(
        "HeadingKo",
        parent=sample["Heading2"],
        fontName="NanumGothicBold",
        fontSize=12,
        leading=17,
        spaceBefore=10,
        spaceAfter=5,
    )
    body = ParagraphStyle(
        "BodyKo",
        parent=sample["BodyText"],
        fontName="NanumGothic",
        fontSize=10,
        leading=15,
        spaceAfter=5,
        wordWrap="CJK",
    )
    return title, heading, body


CONTENT = {
    ROOT / "Linked_List" / "Linked Lists Questions KOR.pdf": {
        "title": "연결 리스트 문제집 번역본 (KOR)",
        "subtitle": "원본: Linked Lists Questions.pdf",
        "items": [
            (
                "안내",
                [
                    "APAS에 제공된 프로그램 템플릿을 사용해 빈 함수를 구현하는 형식의 문제들입니다.",
                    "기본 연결 리스트 조작 함수는 이미 주어져 있으며, 요구된 함수만 완성하면 됩니다.",
                ],
            ),
            (
                "문제 1. insertSortedLL",
                [
                    "정수 item을 오름차순 단일 연결 리스트에 정렬 상태를 유지하며 삽입하는 함수를 작성합니다.",
                    "이미 같은 값이 리스트에 있으면 삽입하지 않아야 하며, 이 경우 -1을 반환합니다.",
                    "성공하면 새 값이 들어간 인덱스를 반환합니다.",
                    "전제: 입력 리스트는 비어 있거나 이미 오름차순 정렬 상태입니다.",
                ],
            ),
            (
                "문제 2. alternateMergeLL",
                [
                    "두 번째 리스트의 노드들을 첫 번째 리스트의 교차 위치에 하나씩 삽입합니다.",
                    "첫 번째 리스트에서 교차로 끼워 넣을 수 있는 자리까지만 삽입합니다.",
                    "첫 번째 리스트가 더 길면 두 번째 리스트는 비게 될 수 있고, 두 번째 리스트가 더 길면 남는 노드는 그대로 유지됩니다.",
                ],
            ),
            (
                "문제 3. moveOddItemsToBackLL",
                [
                    "리스트에 들어 있는 모든 홀수를 뒤쪽으로 이동시킵니다.",
                    "짝수들의 상대적 순서와 홀수들의 상대적 순서는 유지되는 예시가 제시되어 있습니다.",
                ],
            ),
            (
                "문제 4. moveEvenItemsToBackLL",
                [
                    "리스트에 들어 있는 모든 짝수를 뒤쪽으로 이동시킵니다.",
                    "홀수 구간과 짝수 구간 각각의 상대적 순서를 유지하는 형태의 결과가 예시로 주어집니다.",
                ],
            ),
            (
                "문제 5. frontBackSplitLL",
                [
                    "하나의 단일 연결 리스트를 앞쪽 절반과 뒤쪽 절반 두 개의 리스트로 분리합니다.",
                    "노드 수가 홀수이면 앞쪽 리스트가 한 개 더 많이 가져갑니다.",
                    "결과는 frontList와 backList 두 리스트로 출력합니다.",
                ],
            ),
            (
                "참고",
                [
                    "원본 PDF 후반부의 일부 텍스트는 추출 상태가 좋지 않았지만, 확인 가능한 문제 설명 기준으로 핵심 요구사항을 모두 옮겼습니다.",
                ],
            ),
        ],
    },
    ROOT / "Stack_and_Queue" / "Stack and Queues Questions KOR.pdf": {
        "title": "스택과 큐 문제집 번역본 (KOR)",
        "subtitle": "원본: Stack and Queues Questions.pdf",
        "items": [
            (
                "안내",
                [
                    "APAS 템플릿을 사용해 스택과 큐 관련 함수들을 구현하는 문제들입니다.",
                    "문제에 따라 push/pop, enqueue/dequeue만 사용하라는 제한이 있습니다.",
                ],
            ),
            (
                "문제 1. createQueueFromLinkedList",
                [
                    "연결 리스트에 저장된 모든 정수를 순서대로 큐에 넣어 연결 리스트 기반 큐를 생성합니다.",
                    "첫 번째 노드부터 마지막 노드까지 차례대로 enqueue 해야 합니다.",
                    "큐가 비어 있지 않다면 먼저 비워야 합니다.",
                ],
            ),
            (
                "문제 2. createStackFromLinkedList",
                [
                    "연결 리스트에 저장된 모든 정수를 순서대로 스택에 push 하여 연결 리스트 기반 스택을 생성합니다.",
                    "첫 번째 노드부터 순서대로 push 하므로 최종 스택의 top은 마지막 원소가 됩니다.",
                    "스택이 비어 있지 않다면 먼저 비워야 합니다.",
                ],
            ),
            (
                "문제 3. isStackPairwiseConsecutive",
                [
                    "스택의 원소들이 두 개씩 짝을 이뤄 연속된 수인지 검사합니다.",
                    "예: (16, 15), (11, 10), (5, 4)는 모두 절댓값 차이가 1이므로 참입니다.",
                    "push와 pop만 사용하여 검사해야 합니다.",
                    "원소 수가 홀수인 경우는 거짓입니다.",
                ],
            ),
            (
                "문제 4. reverseQueue",
                [
                    "스택 하나를 사용해 큐의 순서를 뒤집습니다.",
                    "스택 조작은 push/pop, 큐 조작은 enqueue/dequeue만 사용해야 합니다.",
                ],
            ),
            (
                "문제 5. recursiveReverseQueue",
                [
                    "재귀 함수로 큐의 순서를 뒤집습니다.",
                    "앞 원소를 dequeue 한 뒤 재귀 호출을 하고, 복귀하면서 enqueue 하는 전형적인 방식입니다.",
                ],
            ),
            (
                "문제 6. removeUntilStack",
                [
                    "스택 top에서부터 값을 pop 하다가, 지정한 값 value가 처음 나타나면 그 값은 남기고 중단합니다.",
                    "예를 들어 top이 왼쪽일 때 (1, 2, 3, 4, 5, 6, 7)에서 value가 4이면 결과는 (4, 5, 6, 7)입니다.",
                ],
            ),
            (
                "문제 7. balanced",
                [
                    "문자열 속 괄호 문자 ()[]{} 가 균형 잡혀 있는지 검사합니다.",
                    "열린 괄호는 스택에 넣고, 닫힌 괄호를 만나면 스택 top과 짝이 맞는지 확인하는 방식입니다.",
                    "예: (), ([]), {[]()[]} 는 balanced이고, {{)] 와 [({{)]) 는 not balanced입니다.",
                ],
            ),
        ],
    },
    ROOT / "Binary_Tree" / "Binary Trees Questions KOR.pdf": {
        "title": "이진 트리 문제집 번역본 (KOR)",
        "subtitle": "원본: Binary Trees Questions.pdf",
        "items": [
            (
                "안내",
                [
                    "빈 이진 트리와 재귀를 다루는 기본 문제들입니다.",
                    "입력 예시에서 알파벳 문자를 넣으면 NULL 자식으로 처리합니다.",
                ],
            ),
            (
                "문제 1. identical",
                [
                    "두 이진 트리 tree1, tree2가 구조적으로 동일한지 재귀적으로 판별합니다.",
                    "두 트리가 모두 비어 있으면 참이고, 둘 다 비어 있지 않으면 루트 값이 같고 왼쪽/오른쪽 서브트리도 각각 동일해야 합니다.",
                    "같으면 1, 아니면 0을 반환합니다.",
                ],
            ),
            (
                "문제 2. maxHeight",
                [
                    "루트에서 가장 먼 리프까지의 링크 수, 즉 트리의 최대 높이를 반환합니다.",
                    "빈 트리의 높이는 -1로 간주합니다.",
                ],
            ),
            (
                "문제 3. countOneChildNodes",
                [
                    "정확히 한 개의 자식만 가진 노드의 개수를 반환합니다.",
                    "왼쪽만 있거나 오른쪽만 있는 노드를 세면 됩니다.",
                ],
            ),
            (
                "문제 4. sumOfOddNodes",
                [
                    "이진 트리 안의 모든 홀수 값의 합을 재귀적으로 구합니다.",
                ],
            ),
            (
                "문제 5. mirrorTree",
                [
                    "주어진 이진 트리를 제자리에서 좌우가 뒤바뀐 거울 트리로 만듭니다.",
                    "중간 트리나 임시 트리를 새로 만들지 말아야 합니다.",
                ],
            ),
            (
                "추가 메모",
                [
                    "원본 PDF에는 이후 페이지에 이어지는 문제가 더 있을 가능성이 있지만, 추출 가능한 범위에서 명확히 확인된 항목은 여기까지였습니다.",
                ],
            ),
        ],
    },
    ROOT / "Binary_Search_Tree" / "Binary Search Trees Questions KOR.pdf": {
        "title": "이진 탐색 트리 문제집 번역본 (KOR)",
        "subtitle": "원본: Binary Search Trees Questions.pdf",
        "items": [
            (
                "안내",
                [
                    "반복문과 스택/큐를 이용해 BST 순회를 구현하는 문제들입니다.",
                ],
            ),
            (
                "문제 1. levelOrderIterative",
                [
                    "큐를 사용해 레벨 순서 순회(level-order traversal)를 출력합니다.",
                    "루트 레벨부터 시작하며 enqueue/dequeue만 사용해야 합니다.",
                    "큐가 비어 있지 않으면 먼저 비워야 합니다.",
                ],
            ),
            (
                "문제 2. inOrderIterative",
                [
                    "스택을 사용해 BST의 중위 순회(in-order traversal)를 반복적으로 출력합니다.",
                    "push/pop만 사용해야 하며, 스택이 비어 있지 않으면 먼저 비워야 합니다.",
                ],
            ),
            (
                "문제 3. preOrderIterative",
                [
                    "스택을 사용해 BST의 전위 순회(pre-order traversal)를 반복적으로 출력합니다.",
                ],
            ),
            (
                "문제 4. postOrderIterativeS1",
                [
                    "스택 하나를 사용해 BST의 후위 순회(post-order traversal)를 반복적으로 출력합니다.",
                ],
            ),
            (
                "문제 5. postOrderIterativeS2",
                [
                    "스택 두 개를 사용해 BST의 후위 순회를 반복적으로 출력합니다.",
                    "두 스택 모두 비어 있지 않다면 먼저 비워야 합니다.",
                ],
            ),
        ],
    },
}


def build_pdf(target: Path, title_text: str, subtitle: str, items) -> None:
    title_style, heading_style, body_style = build_styles()
    doc = SimpleDocTemplate(
        str(target),
        pagesize=A4,
        leftMargin=18 * mm,
        rightMargin=18 * mm,
        topMargin=18 * mm,
        bottomMargin=18 * mm,
        title=title_text,
        author="Codex",
    )
    story = [
        Paragraph(title_text, title_style),
        Paragraph(subtitle, body_style),
        Spacer(1, 6),
    ]
    for heading, bullets in items:
        story.append(Paragraph(heading, heading_style))
        for bullet in bullets:
            story.append(Paragraph(f"- {bullet}", body_style))
        story.append(Spacer(1, 4))
    doc.build(story)


def main() -> None:
    register_fonts()
    for target, spec in CONTENT.items():
        build_pdf(target, spec["title"], spec["subtitle"], spec["items"])
        print(f"generated: {target}")


if __name__ == "__main__":
    main()
