# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    find_co.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/14 13:27:30 by jnovotny          #+#    #+#              #
#    Updated: 2019/11/13 12:24:03 by jnovotny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

find . -type f -name "*.c" -exec basename {} \; | awk '{print "\t\t"$0" \\"}' > list_c
