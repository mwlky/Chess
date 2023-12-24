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

  bool checkSite = CheckSite(*m_DraggedPawn);
  bool isValid = m_DraggedPawn->IsValidMove(newX, newY);
  auto pieceOnSquare = m_Squares.squares[newX][newY].GetAssignedPawn();

  if (pieceOnSquare != nullptr &&
      pieceOnSquare->GetSite() == m_DraggedPawn->GetSite())
    isValid = false;

  if (!isValid || !CheckIfPathIsClear(*m_DraggedPawn, newX, newY) ||
      !checkSite) {
    m_SquareThatPawnIsDraggedFrom->AssignPiece(m_DraggedPawn, false);

    m_DraggedPawn = nullptr;
    return;
  }

  SwitchSite();

  m_SquareThatPawnIsDraggedFrom->UnassignPiece();
  m_SquareThatPawnIsDraggedFrom = nullptr;

  m_Squares.squares[newX][newY].AssignPiece(m_DraggedPawn, true);
  m_DraggedPawn = nullptr;
}

bool Board::CheckIfPathIsClear(const Piece &piece, int newX, int newY) {

  if (typeid(Knight) == typeid(piece)) {
    return true;
  }

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
} // namespace Chess