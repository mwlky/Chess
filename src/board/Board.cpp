#include "Board.h"

namespace Chess {
    void Board::RenderBoard() {

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                m_Squares.squares[i][j].Render();
            }
        }
    }

    void Board::CreateBoard(int screenWidth, int screenHeight) {
        Squares squares;

        bool white = true;

        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {

                const char *path = nullptr;

                if (white)
                    path = WHITE_SQUARE;

                else
                    path = BLACK_SQUARE;

                SDL_Rect rect = {x * screenWidth / 8, y * screenHeight / 8,
                                 screenWidth / 8, screenHeight / 8};

                Square square(path, Window::Renderer, rect);
                squares.squares[x][y] = square;

                white = !white;
            }
            white = !white;
        }

        m_Squares = squares;
        SetPieces();
    }

    void Board::TakePiece(int x, int y) {
        m_DraggedPawn = m_Squares.squares[x][y].GetAssignedPawn();
        if (m_DraggedPawn != nullptr) {
            m_SquareThatPawnIsDraggedFrom = &m_Squares.squares[x][y];
        }
    }

    void Board::SetPieces() {
        auto blackKnightLeft =
                std::make_shared<Knight>(KNIGHT_BLACK, Piece::Site::BLACK, 1, 0);
        m_Squares.squares[1][0].AssignPiece(blackKnightLeft, false);

        auto blackKnightRight =
                std::make_shared<Knight>(KNIGHT_BLACK, Piece::Site::BLACK, 6, 0);
        m_Squares.squares[6][0].AssignPiece(blackKnightRight, false);

        auto whiteKnightLeft =
                std::make_shared<Knight>(KNIGHT_WHITE, Piece::Site::WHITE, 1, 7);
        m_Squares.squares[1][7].AssignPiece(whiteKnightLeft, false);

        auto whiteKnightRight =
                std::make_shared<Knight>(KNIGHT_WHITE, Piece::Site::WHITE, 6, 7);
        m_Squares.squares[6][7].AssignPiece(whiteKnightRight, false);

        auto blackRookRight =
                std::make_shared<Rook>(ROOK_BLACK, Piece::Site::BLACK, 7, 0);
        m_Squares.squares[7][0].AssignPiece(blackRookRight, false);

        auto blackRookLeft =
                std::make_shared<Rook>(ROOK_BLACK, Piece::Site::BLACK, 0, 0);
        m_Squares.squares[0][0].AssignPiece(blackRookLeft, false);

        auto whiteRookRight =
                std::make_shared<Rook>(ROOK_WHITE, Piece::Site::WHITE, 0, 7);
        m_Squares.squares[0][7].AssignPiece(whiteRookRight, false);

        auto whiteRookLeft =
                std::make_shared<Rook>(ROOK_WHITE, Piece::Site::WHITE, 7, 7);
        m_Squares.squares[7][7].AssignPiece(whiteRookLeft, false);

        auto whiteBishopRight =
                std::make_shared<Bishop>(BISHOP_WHITE, Piece::Site::WHITE, 5, 7);
        m_Squares.squares[5][7].AssignPiece(whiteBishopRight, false);

        auto whiteBishopLeft =
                std::make_shared<Bishop>(BISHOP_WHITE, Piece::Site::WHITE, 2, 7);
        m_Squares.squares[2][7].AssignPiece(whiteBishopLeft, false);

        auto blackBishopRight =
                std::make_shared<Bishop>(BISHOP_BLACK, Piece::Site::BLACK, 2, 0);
        m_Squares.squares[2][0].AssignPiece(blackBishopRight, false);

        auto blackBishopLeft =
                std::make_shared<Bishop>(BISHOP_BLACK, Piece::Site::BLACK, 5, 0);
        m_Squares.squares[5][0].AssignPiece(blackBishopLeft, false);

        auto blackQueen =
                std::make_shared<Queen>(QUEEN_BLACK, Piece::Site::BLACK, 3, 0);
        m_Squares.squares[3][0].AssignPiece(blackQueen, false);

        auto whiteQueen =
                std::make_shared<Queen>(QUEEN_WHITE, Piece::Site::WHITE, 3, 7);
        m_Squares.squares[3][7].AssignPiece(whiteQueen, false);

        auto blackKing = std::make_shared<King>(KING_BLACK, Piece::Site::BLACK, 4, 0);
        m_Squares.squares[4][0].AssignPiece(blackKing, false);

        auto whiteKing = std::make_shared<King>(KING_WHITE, Piece::Site::WHITE, 4, 7);
        m_Squares.squares[4][7].AssignPiece(whiteKing, false);

        for (int i = 0; i < 8; ++i) {
            auto whitePawn =
                    std::make_shared<Pawn>(PAWN_WHITE, Piece::Site::WHITE, i, 0);
            m_Squares.squares[i][6].AssignPiece(whitePawn, false);
        }

        for (int i = 0; i < 8; ++i) {
            auto blackPawn =
                    std::make_shared<Pawn>(PAWN_BLACK, Piece::Site::BLACK, i, 0);
            m_Squares.squares[i][1].AssignPiece(blackPawn, false);
        }
    }

    void Board::MoveDraggedPawn() {
        if (m_DraggedPawn == nullptr)
            return;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int pawnX = mouseX - m_DraggedPawn->GetRect().w / 2;
        int pawnY = mouseY - m_DraggedPawn->GetRect().h / 2;

        m_DraggedPawn->SetGlobalPosition(pawnX, pawnY);
    }

    void Board::ReleasePiece() {
        if (m_DraggedPawn == nullptr)
            return;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int newX = mouseX / 100;
        int newY = mouseY / 100;

        auto piece = m_Squares.squares[newX][newY].GetAssignedPawn();

        bool checkSite = CheckSite(*m_DraggedPawn);
        bool isValid = CheckIfMoveIsProper(newX, newY, piece);
        bool isCastling = IsTryingToCastle(newX, newY);

        if(CheckCheck()){
            if(!HasTriedToSaveKing(newX, newY))
            {
                CancelMove();
                return;
            }

            SwitchSite();
            DoNormalMove(newX, newY);
            return;
        }

        if (isCastling) {
            DoCastle(newX);
        }

        else if (!isValid || !CheckIfPathIsClear(*m_DraggedPawn, newX, newY) || !checkSite) {
            CancelMove();

            return;
        }
        SwitchSite();
        DoNormalMove(newX, newY);
    }

    void Board::DoNormalMove(int newX, int newY) {
        m_SquareThatPawnIsDraggedFrom->UnassignPiece();
        m_SquareThatPawnIsDraggedFrom = nullptr;

        m_Squares.squares[newX][newY].UnassignPiece();
        m_Squares.squares[newX][newY].AssignPiece(m_DraggedPawn, true);
        m_DraggedPawn = nullptr;
    }

    bool Board::IsTryingToCastle(int newX, int newY) {
        if (typeid(*m_DraggedPawn) != typeid(King))
            return false;

        if (m_DraggedPawn->HasMoved)
            return false;

        int deltaX = newX - m_DraggedPawn->GetBoardXPosition();

        if (abs(deltaX) != 2)
            return false;

        if (!CheckIfPathIsClear(*m_DraggedPawn, newX, newY))
            return false;

        if(IsPathUnderAttack(m_DraggedPawn->GetBoardXPosition(), newX, newY, m_DraggedPawn->GetSite()))
            return false;

        return true;
    }

    void Board::CancelMove() {
        m_SquareThatPawnIsDraggedFrom->AssignPiece(m_DraggedPawn, false);

        m_DraggedPawn = nullptr;
    }

    bool Board::CheckIfMoveIsProper(int newX, int newY,
                               const std::shared_ptr<Piece> &piece) const {
        Piece::MoveType moveType = Piece::MoveType::NORMAL;

        bool isValid;

        if (piece != nullptr &&
            piece->GetSite() == m_DraggedPawn->GetSite())
            isValid = false;

        else if (piece != nullptr && piece->GetSite() != m_DraggedPawn->GetSite()) {
            moveType = Piece::MoveType::TAKE;
            isValid = m_DraggedPawn->IsValidMove(newX, newY, moveType);
        } else
            isValid = m_DraggedPawn->IsValidMove(newX, newY, moveType);
        return isValid;
    }

    bool Board::CheckIfPathIsClear(const Piece &piece, int newX, int newY) const{

        if (typeid(Knight) == typeid(piece))
            return true;

        int directionX = newX - piece.GetBoardXPosition() > 0
                         ? 1
                         : ((newX - piece.GetBoardXPosition()) < 0 ? -1 : 0);
        int directionY = newY - piece.GetBoardYPosition() > 0
                         ? 1
                         : ((newY - piece.GetBoardYPosition()) < 0 ? -1 : 0);

        for (int x = piece.GetBoardXPosition() + directionX,
                     y = piece.GetBoardYPosition() + directionY;
             x != newX || y != newY; x += directionX, y += directionY) {

            if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                return false;
            }

            if (m_Squares.squares[x][y].GetAssignedPawn() != nullptr) {
                return false;
            }
        }
        return true;
    }

    bool Board::CheckSite(const Piece &piece) {

        Piece::Site pieceSite = piece.GetSite();

        if (m_CurrentMove == pieceSite) {
            return true;
        }

        return false;
    }

    void Board::SwitchSite() {

        if (m_CurrentMove == Piece::Site::BLACK)
            m_CurrentMove = Piece::Site::WHITE;

        else
            m_CurrentMove = Piece::Site::BLACK;
    }

    bool Board::IsSquareUnderAttack(int x, int y, Piece::Site site) const{

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                auto attackingPiece = m_Squares.squares[i][j].GetAssignedPawn();

                if (attackingPiece != nullptr && attackingPiece->GetSite() != site)
                    if (attackingPiece->IsValidMove(x, y, Piece::MoveType::TAKE) &&
                        CheckIfPathIsClear(*attackingPiece, x, y))
                        return true;
            }
        }

        return false;
    }

    void Board::DoCastle(int newX) {
        int deltaX = newX - m_DraggedPawn->GetBoardXPosition();

        int rookX = (deltaX > 0) ? 7 : 0;
        int rookY = (m_DraggedPawn->GetSite() == Piece::Site::WHITE) ? 7 : 0;
        auto rook = m_Squares.squares[rookX][rookY].GetAssignedPawn();

        if (rook != nullptr && !rook->HasMoved) {
            int middleX = (deltaX > 0) ? 5 : 3;
            if (m_Squares.squares[middleX][rookY].GetAssignedPawn() == nullptr &&
                m_Squares.squares[newX][rookY].GetAssignedPawn() == nullptr) {

                m_Squares.squares[rookX][rookY].UnassignPiece();
                m_Squares.squares[middleX][rookY].AssignPiece(rook, true);
            }
        }
    }

    bool Board::IsPathUnderAttack(int xStart, int xEnd, int y,Piece::Site site) const {
        int direction = xEnd - xStart;
        int directionNormalized = direction > 0 ? 1 : -1;

        for (int x = xStart;
             x != xEnd + directionNormalized; x += directionNormalized) {

            if (x < 0 || x >= 8) {
                return false;
            }

            if (IsSquareUnderAttack(x, y, site)) {
                return true;
            }
        }

        return false;
    }

    bool Board::IsCheckmate(Piece::Site site){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                auto currentPiece = m_Squares.squares[i][j].GetAssignedPawn();

                if (currentPiece != nullptr && currentPiece->GetSite() == site) {
                    for (int newX = 0; newX < 8; newX++) {
                        for (int newY = 0; newY < 8; newY++) {
                            if (CheckIfMoveIsProper(newX, newY, nullptr)) {
                                auto originalSquare = m_Squares.squares[i][j];
                                auto originalPiece = currentPiece;

                                m_Squares.squares[i][j].UnassignPiece();
                                m_Squares.squares[newX][newY].AssignPiece(originalPiece, true);

                                bool isInCheck = IsSquareUnderAttack(originalPiece->GetBoardXPosition(),
                                                                     originalPiece->GetBoardYPosition(),
                                                                     site);

                                m_Squares.squares[i][j] = originalSquare;
                                m_Squares.squares[newX][newY].UnassignPiece();
                                m_Squares.squares[i][j].AssignPiece(originalPiece, true);

                                if (!isInCheck) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }

        return true;
    }

    bool Board::CheckCheck() {
        auto king = FindKingOfSite(m_CurrentMove);

        int xPos = king->GetBoardXPosition();
        int yPos = king->GetBoardYPosition();

        return IsSquareUnderAttack(xPos, yPos, m_CurrentMove);
    }

    Piece* Board::FindKingOfSite(Piece::Site site) {
        for (const auto & square : m_Squares.squares) {
            for (const auto & y : square) {
                auto piece = y.GetAssignedPawn();

                if(piece == nullptr)
                    continue;

                if(dynamic_cast<King*>(piece.get()) == nullptr)
                    continue;

                if(piece->GetSite() != site)
                    continue;

                return piece.get();
            }
        }

        return nullptr;
    }

    bool Board::HasTriedToSaveKing(const int& newX, const int& newY) {
        auto king = dynamic_cast<King*>(m_DraggedPawn.get());

        if(king != nullptr)
        {
            if(king->IsValidMove(newX, newY, Piece::MoveType::NORMAL) && !IsSquareUnderAttack(newX, newY, king->GetSite())){
                if(CheckIfPathIsClear(*king, newX, newY))
                    return true;
            }
        } else{

            if(m_DraggedPawn->IsValidMove(newX, newY, Piece::MoveType::NORMAL) || m_DraggedPawn->IsValidMove(newX, newY, Piece::MoveType::TAKE)){

                auto king = FindKingOfSite(m_CurrentMove);

                m_SquareThatPawnIsDraggedFrom->UnassignPiece();
                m_Squares.squares[newX][newY].AssignPiece(m_DraggedPawn, true);

                if(!IsSquareUnderAttack(king->GetBoardXPosition(), king->GetBoardYPosition(), m_CurrentMove))
                    return true;


                return false;
            }
        }

        return false;
    }
} // namespace Chess