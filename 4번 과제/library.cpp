#include <iostream>
#include <vector>
#include <string>
 #include <unordered_map>
using namespace std; // namespace std 사용


class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};
class BorrowManager {
private:
    unordered_map<string, int>stock ; // 책 제목과 대출 횟수를 저장하는 맵
    int quantity = 3; // 초기 대출 가능 수량을 설정하는 변수

public:
	
	void initializeStock(const string& title) { // 책 제목과 초기 대출 가능 수량을 설정하는 메서드
        stock[title] = quantity; // 맵에 책 제목과 수량을 추가
    } 
    void borrowBook(const string& title) {
        if (stock.find(title) != stock.end()) {
            if (stock[title] > 0) {
                stock[title]--;
                cout << "책 '" << title << "'을(를) 대출했습니다. 남은 수량: " << stock[title] << endl;
            }
            else {
                cout << "책 '" << title << "'은(는) 현재 대출 불가합니다." << endl;
            }
        }
        else {
            cout << "책 '" << title << "'은(는) 등록되지 않았습니다." << endl;
        }
    }

        
    void returnBook(const string& title) {
        if (stock.find(title) != stock.end()) {
            stock[title]++;
            cout << "책 '" << title << "'을(를) 반납했습니다. 현재 수량: " << stock[title] << endl;
        }
        else {
            cout << "책 '" << title << "'은(는) 등록되지 않았습니다." << endl;
        }
    }

    // 현재 재고 상태 출력
    void displayStock() const {
        cout << "📚 현재 대출 가능 목록:" << endl;
        for (const auto& pair : stock) {
            cout << "- " << pair.first << " : " << pair.second << "권 남음" << endl;
        }
    }
};
class BookManager {
private:
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
    void findbookByTitle(const string& title) const {
        bool found = false; // 책이 발견되었는지 여부를 저장하는 변수
        for (const auto& book : books) { // 범위 기반 for문 사용
            if (book.title == title) { // 제목이 일치하는지 확인
                cout << "책을 찾았습니다: " << book.title << " by " << book.author << endl;
                found = true; // 책이 발견되었음을 표시
                break; // 책을 찾았으므로 루프 종료
            }
        }
        if (!found) { // 책이 발견되지 않았을 경우
            cout << "해당 제목의 책을 찾을 수 없습니다." << endl;
        }
	}
    void findbookByAuthor(const string& author) const {
        bool found = false; // 책이 발견되었는지 여부를 저장하는 변수
        for (const auto& book : books) { // 범위 기반 for문 사용
            if (book.author == author) { // 저자명이 일치하는지 확인
                cout << "책을 찾았습니다: " << book.title << " by " << book.author << endl;
                found = true; // 책이 발견되었음을 표시
            }
        }
        if (!found) { // 책이 발견되지 않았을 경우
            cout << "해당 저자의 책을 찾을 수 없습니다." << endl;
        }
	}
};



int main() {
    BookManager manager;
    BorrowManager borrowManager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "3. 책 찾기" << endl; // 책 제목 또는 저자명으로 책 검색
		cout << "4. 책 대여 여부 확인" << endl; // 대출 가능한 책 목록 출력 및 대출 처리
		cout << "5. 반납" << endl; // 반납  입력받아 책 반납 처리
        cout << "6. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            borrowManager.initializeStock(title);
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            // 3번 선택: 책 찾기
            // 사용자로부터 책 제목 또는 저자명을 입력받아 해당 책을 검색합니다.
            int searchChoice;
            cout << "1. 제목으로 찾기" << endl; // 제목으로 책 검색
            cout << "2. 저자명으로 찾기" << endl; // 저자명으로 책 검색
            cout << "선택: ";
            cin >> searchChoice;
            string input;
            if (searchChoice == 1) {
                // 제목으로 찾기 선택
                cout << "책 제목: ";
                cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
                getline(cin, input); // 제목 입력 (공백 포함)
                manager.findbookByTitle(input); // 입력받은 제목으로 책 검색
            }
            else if (searchChoice == 2) {
                // 저자명으로 찾기 선택
                cout << "저자명: ";
                cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
                getline(cin, input); // 저자명 입력 (공백 포함)
                manager.findbookByAuthor(input); // 입력받은 저자명으로 책 검색
            }
            else {
                cout << "잘못된 선택입니다." << endl; // 잘못된 선택 처리
            }
       
		}
        else if (choice == 4) {
			borrowManager.displayStock(); // 현재 대출 가능한 책 목록을 출력합니다.
            string title;
            cout << "대출할 책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 대출할 책 제목 입력 (공백 포함)
            borrowManager.borrowBook(title); // 입력받은 제목으로 책 대출 시도
		}
            
        else if (choice == 5) {
            string title;
            cout << "반납할 책 제목을 입력하세요: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.returnBook(title);

        }
        else if (choice == 6) {
            cout << "프로그램을 종료합니다." << endl;
            break;

        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}

    