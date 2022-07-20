## 에러 로그

```bash
{
  url: '/debates/search',
  response: { statusCode: 500, message: 'Internal Server Error' },
  stack: "QueryFailedError: Unknown column 'NaN' in 'where clause'\n" +
    '    at QueryFailedError.TypeORMError [as constructor] (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/src/error/TypeORMError.ts:7:9)\n' +
    '    at new QueryFailedError (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/src/error/QueryFailedError.ts:9:9)\n' +
    '    at Query.onResult (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/src/driver/mysql/MysqlQueryRunner.ts:183:37)\n' +
    '    at Query.execute (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/node_modules/mysql2/lib/commands/command.js:36:14)\n' +
    '    at PoolConnection.handlePacket (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/node_modules/mysql2/lib/connection.js:456:32)\n' +
    '    at PacketParser.onPacket (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/node_modules/mysql2/lib/connection.js:85:12)\n' +
    '    at PacketParser.executeStart (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/node_modules/mysql2/lib/packet_parser.js:75:16)\n' +
    '    at Socket.<anonymous> (/Users/sangbongpark/Desktop/codestates/SuSang-YuHee/Debate-Ducks-Server/Debate-Ducks-Server/node_modules/mysql2/lib/connection.js:92:25)\n' +
    '    at Socket.emit (node:events:390:28)\n' +
    '    at addChunk (node:internal/streams/readable:315:12)'
}
```

## 에러가 발생한 상황의 코드

```ts
import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  Patch,
  Post,
} from "@nestjs/common";
import { Response } from "express";
import { DebateInfo } from "./DebateInfo";
import { DebatesService } from "./debates.service";
import { CreateDebateDto } from "./dto/create-debate.dto";
import { GetDebatesDto } from "./dto/get-debates-forum.dto";
import { SearchDebatesDto } from "./dto/search-debates-forum.dto";
import { UpdateDebateDto } from "./dto/update-debate.dto";

@Controller("debates")
export class DebatesController {
  constructor(private debatesService: DebatesService) {}

  @Post()
  async createDebate(@Body() dto: CreateDebateDto): Promise<number> {
    console.log(dto);
    const { title, author_id, author_pros, category, contents } = dto;
    return await this.debatesService.createDebate(
      title,
      author_id,
      author_pros,
      category,
      contents,
    );
  }

  @Get("/:id")
  async getDebateInfo(@Param("id") debateId: number): Promise<DebateInfo> {
    console.log(debateId);
    return this.debatesService.getDebateInfo(debateId);
  }

  @Get("/search")
  async searchDebates(@Body() dto: SearchDebatesDto) {
    return this.debatesService.searchDebates(dto);
  }

  @Get()
  async getDebates(@Body() dto: GetDebatesDto) {
    return this.debatesService.getDebates(dto);
  }

  @Patch()
  async updateDebateInfo(@Body() dto: UpdateDebateDto): Promise<any> {
    return await this.debatesService.updateDebate(dto);
  }

  @Delete("/:id")
  async deleteDebate(@Param("id") debateId: number): Promise<void> {
    console.log(debateId);
    await this.debatesService.deleteDebate(debateId);
  }
}
```

## 발생 원인

### 컨트롤러에서 get 요청을 받을 때 debates/search 경로로 들어오기 전 debates/:id에 걸리게 되고 id 값이 존재하지 않기 때문에 NaN으로 로그가 찍혀나오는 것을 알 수 있었다.

## 해결 방법

### 아름다운 해결법은 아니지만 debates/:id 보다 debates/search 를 먼저 둠으로써 해결

```ts
import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  Patch,
  Post,
} from "@nestjs/common";
import { Response } from "express";
import { DebateInfo } from "./DebateInfo";
import { DebatesService } from "./debates.service";
import { CreateDebateDto } from "./dto/create-debate.dto";
import { GetDebatesDto } from "./dto/get-debates-forum.dto";
import { SearchDebatesDto } from "./dto/search-debates-forum.dto";
import { UpdateDebateDto } from "./dto/update-debate.dto";

@Controller("debates")
export class DebatesController {
  constructor(private debatesService: DebatesService) {}

  @Post()
  async createDebate(@Body() dto: CreateDebateDto): Promise<number> {
    console.log(dto);
    const { title, author_id, author_pros, category, contents } = dto;
    return await this.debatesService.createDebate(
      title,
      author_id,
      author_pros,
      category,
      contents,
    );
  }

  @Get("/search")
  async searchDebates(@Body() dto: SearchDebatesDto) {
    return this.debatesService.searchDebates(dto);
  }

  @Get("/:id")
  async getDebateInfo(@Param("id") debateId: number): Promise<DebateInfo> {
    console.log(debateId);
    return this.debatesService.getDebateInfo(debateId);
  }

  @Get()
  async getDebates(@Body() dto: GetDebatesDto) {
    return this.debatesService.getDebates(dto);
  }

  @Patch()
  async updateDebateInfo(@Body() dto: UpdateDebateDto): Promise<any> {
    return await this.debatesService.updateDebate(dto);
  }

  @Delete("/:id")
  async deleteDebate(@Param("id") debateId: number): Promise<void> {
    console.log(debateId);
    await this.debatesService.deleteDebate(debateId);
  }
}
```